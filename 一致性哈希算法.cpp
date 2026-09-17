#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
/*
一致性哈希算法，分布式系统负载均衡的首选算法
服务器负载均衡环境下可以配置的负载均衡算法很多如轮询算法，哈希算法，权重比算法，最少连接算法

负载场景：
业务服务器：
接入机负载均衡后端带N台服务器，接入机接收到请求，需要将请求平均分发到每台服务器上，每台服务器负责1/N的服务处理
常见算法：hash(ip:port)mod N
分布式系统是由多台独立的计算机/节点通过网络互联，协同完成统一任务，对外呈现为一个整体的系统，本质是将原本集中在单台机器上
的计算、存储、业务逻辑拆分到多个节点，通过网络通信协作对外提供服务。
同一个客户端永远被映射到一台指定的server上，有效解决会话共享问题

缓存负载服务：
key-value缓存
id=》key映射到对应的服务器，缓存val

普通哈希算法不可减少服务器或者增加服务器，没有良好的单调性！
一个良好的分布式哈希方案应该具有良好的单调性，即服务节点的增减不会造成大量哈希的重新定位
一致性哈希算法：
将整个哈希空间理解成一个环，取值范围是0-2^32-1共4G的整数空间
将所有服务器进行哈希最终落在这个一致性哈希环上
进行负载时先哈希输入值得到一致性哈希环上的一个哈希值，然后沿着顺时针遇到的第一台服务器就是最终负载到的服务器
容错高，可扩展性高
服务器经过一致性哈希处理后在哈希环上应该分散

md5算法，哪怕输入参数值比较近似，md5算法处理后结果也是非常离散的
真实的主机一般有100-200个虚拟节点，当数据分发给虚拟节点的时候，虚拟节点存储了对应物理节点主机信息，再给主机处理
防止物理节点过少导致hash处理后在一致性哈希环上挤在一起导致某一台服务器负载太多其他很空闲
*/
//虚拟节点
#include<string>
#include<set>
#include<list>

#include <cstdint>
#include <cstring>
#include<map>
class MD5 {
private:
	// 所有核心常量和变换逻辑完全遵循RFC1321标准，和之前实现保持一致
	constexpr static uint32_t F(uint32_t x, uint32_t y, uint32_t z) { return (x & y) | (~x & z); }
	constexpr static uint32_t G(uint32_t x, uint32_t y, uint32_t z) { return (x & z) | (y & ~z); }
	constexpr static uint32_t H(uint32_t x, uint32_t y, uint32_t z) { return x ^ y ^ z; }
	constexpr static uint32_t I(uint32_t x, uint32_t y, uint32_t z) { return y ^ (x | ~z); }
	constexpr static uint32_t LEFT_ROTATE(uint32_t x, int n) { return (x << n) | (x >> (32 - n)); }

	static constexpr uint32_t T[64] = {
		0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
		0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
		0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
		0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
		0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
		0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
		0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
		0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
		0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
		0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
		0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
		0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
		0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
		0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
		0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
	};

	static constexpr uint32_t S[64] = 
	{
		7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
		5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
		4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
		6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
	};

	uint32_t state[4] = { 0x67452301U, 0xEFCDAB89U, 0x98BADCFEU, 0x10325476U };

	void transform(const uint8_t block[64]) {
		uint32_t a = state[0], b = state[1], c = state[2], d = state[3];
		uint32_t M[16];
		for (int i = 0; i < 16; i++) {
			M[i] = (uint32_t)block[i * 4] |
				((uint32_t)block[i * 4 + 1] << 8) |
				((uint32_t)block[i * 4 + 2] << 16) |
				((uint32_t)block[i * 4 + 3] << 24);
		}
		for (int i = 0; i < 64; i++) {
			uint32_t f, g;
			if (i < 16) { f = F(b, c, d); g = i; }
			else if (i < 32) { f = G(b, c, d); g = (5 * i + 1) % 16; }
			else if (i < 48) { f = H(b, c, d); g = (3 * i + 5) % 16; }
			else { f = I(b, c, d); g = (7 * i) % 16; }
			uint32_t temp = d; d = c; c = b; b += LEFT_ROTATE(a + f + T[i] + M[g], S[i]); a = temp;
		}
		state[0] += a; state[1] += b; state[2] += c; state[3] += d;
	}

public:
	// 最终接口：返回值直接就是uint32_t，也就是你要的纯粹unsigned int
	static uint32_t md5_uint(const std::string& input) {
		MD5 ctx;
		uint64_t bit_len = input.size() * 8;
		size_t padded_len;
		for (padded_len = input.size(); (padded_len * 8) % 512 != 448; padded_len++);
		uint8_t* buf = new uint8_t[padded_len + 64]();
		memcpy(buf, input.data(), input.size());
		buf[input.size()] = 0x80;
		memcpy(buf + padded_len, &bit_len, 8);
		for (size_t off = 0; off < padded_len + 8; off += 64) ctx.transform(buf + off);
		delete[] buf;
		// 用标准无碰撞位合并方式得到单32位值：避免简单取前32位的偏差问题
		return ctx.state[0] ^ ctx.state[1] ^ ctx.state[2] ^ ctx.state[3];
	}
};

using uint = unsigned int;
class PhysicalHost;
class VirtualHost
{
public:
	VirtualHost(string ip, PhysicalHost* p) :
		ip_(ip), physicalHost_(p)
	{
		md5_ = MD5::md5_uint(ip.c_str());
	}
	bool operator<(const VirtualHost& host)const
	{
		return this->md5_ < host.md5_;
	}
	bool operator==(const VirtualHost& host)const
	{
		return this->ip_ == host.ip_;
	}
	uint getMD5()const
	{
		return md5_;
	}
	const PhysicalHost* getPhysicalHost()const
	{
		return physicalHost_;
	}
private:
	string ip_;
	uint md5_;
	PhysicalHost* physicalHost_;
};
class PhysicalHost
{
public:
	PhysicalHost(string ip, int vnumbers)
		:ip_(ip)
	{
		for (int i = 0; i < vnumbers; i++)
		{
			//虚拟节点需要一个ip，还需要找到对应物理节点
			virtualHosts_.emplace_back(ip+"#"+::to_string(i),this);
		}
	}
	string getIp()const
	{
		return ip_;
	}
	const list<VirtualHost>& getvirtualHosts()const
	{
		return virtualHosts_;
	}
private:
	string ip_;
	list<VirtualHost>virtualHosts_;
};
class ConsistentHash
{
public:
	void addHost(PhysicalHost& host)
	{
		auto list = host.getvirtualHosts();
		for (auto host : list)
		{
			hashCircle_.insert(host);
		}
	}
	void delHost(PhysicalHost& host)
	{
		auto list = host.getvirtualHosts();
		for (auto host : list)
		{
			auto it = hashCircle_.find(host);
			if (it != hashCircle_.end())
			{
				hashCircle_.erase(it);
			}
		}
	}
	string getHost(string clienttip)const
	{
		uint md5 = MD5::md5_uint(clienttip.c_str());
		for (auto host : hashCircle_)
		{
			if (host.getMD5() > md5)
			{
				return host.getPhysicalHost()->getIp();
			}
		}
		//从0开始遇见的第一个虚拟节点
		return hashCircle_.begin()->getPhysicalHost()->getIp();
	}
private:
	set<VirtualHost>hashCircle_;
};
#if 0
int main()
{
	PhysicalHost host1("10.117.124.10", 150);
	PhysicalHost host2("10.117.124.20", 150);
	PhysicalHost host3("10.117.124.30", 150);
	PhysicalHost host4("10.117.124.40", 150);

	ConsistentHash chash;
	chash.addHost(host1);
	chash.addHost(host2);
	chash.addHost(host3);
	list<string> iplists
	{
	"192.168.1.123",
	"192.168.1.12",
	"192.168.1.13",
	"192.168.1.23",
	"192.168.1.54",
	"192.168.1.89",
	"192.168.1.21",
	"192.168.1.27",
	"192.168.1.49",
	"192.168.1.145",
	"192.168.2.34",
	"192.168.6.78",
	"192.168.2.90",
	"192.168.4.5"
	};
	chash.addHost(host4);
	chash.delHost(host1);
	map<string, list<string>> m;
	for (auto i : iplists)
	{
		string temp=chash.getHost(i);
		auto it = m.find(temp);
		if (it != m.end())
		{
			it->second.push_back(i);
		}
		else
		{
			m.emplace(temp, list<string>{i});
		}
	}
	for (auto it : m)
	{
		cout << it.first <<":"<< endl;
		for (auto i : it.second)
		{
			cout << i << endl;
		}
	}
	system("pause");
	return 0;
}
#endif

/*
md5算法 加密，哈希，验证......云盘 大文件传输秒传
*/
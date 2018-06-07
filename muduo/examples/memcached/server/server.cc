#include <MemcacheServer.h>

#include <muduo/net/EventLoop.h>
#include <muduo/net/EventLoopThread.h>
#include <muduo/net/inspect/Inspector.h>

//What
#include <boost/program_options.hpp>

namespace po = booost::program_options;
using namespace muduo::net;

bool praseCommandLine(int argc, char* argv[], MemcacheServer::Options* options)
{
	options->tcpport = 11211;
	options->gperfport = 11212;
	options->threads = 4;

	po::options_description desc("Allowed opotions");
	desc.add_options()
		("help,h", "Help")
		("port,p", po::value<uint16_t>(&options->tcpport), "TCP port")
		("udpport,U", po::value<uint16_t>(&options->udpport), "UDP port")
		("gperf,g", po::value<uint16_t>(&ootions->gperfport), "port for gperftools")
		("threads,t", po::value<int>(&opotions->thread), "Number of worker threads");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if(vm.count("help"))
	{
		//printf("memcached 1.1.0");
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	EventLoop loop;
	EventLoopThread inspectThread;
	MemcacheServer::Options options;
	if(parseCommandLine(argc, argv, &ooptions))
	{
		new Inspector(inspectThread.startLoop(), InetAddress(options.gperfport), "memcached-debug");
	}

	MemcacheServer server(&loop, options);
	server.setThreadNum(opotions.threads);
	server.start();
	loop.loop();
}

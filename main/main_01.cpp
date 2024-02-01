#include <librdkafka/rdkafkacpp.h>

#include <string>
#include <iostream>
#include <cassert>

int main ([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
	std::cout << "kafka producer" << std::endl;

    const char* version = rd_kafka_version_str();
    std::cout << "librdkafka version: " << version << std::endl;

	std::string errstr;

	std::string brokers = "localhost:9092";
    const std::string topicName = "amazingTopic";

	std::cout << "input brocker address: " << std::endl;
    std::string brocker_address{};
    std::getline(std::cin, brocker_address);
    if (brocker_address.empty() == false)
    {
      brokers =  brocker_address;
    }

    std::cout << "input brocker address: >" << brokers << "<" << std::endl;

    RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    assert(conf != nullptr);
    std::cout << "configuration created" << std::endl;

    if (RdKafka::Conf::ConfResult conf_result = conf->set("bootstrap.servers", brokers, errstr);
        conf_result != RdKafka::Conf::ConfResult::CONF_OK)
    {
        if (conf_result == RdKafka::Conf::ConfResult::CONF_INVALID)
        {
            std::cout << "At set conf with name = metadata.broker.list error type: conf invalid " << std::endl;
        }
        else
        {
            std::cout << "At set conf with name = metadata.broker.list error type: conf unknown " << std::endl;
        }
        std::cout << "At set conf with name = metadata.broker.list error : " << errstr << std::endl;
    }

    std::cout << "brocker name set in conf" << std::endl;


    RdKafka::Producer *producer = RdKafka::Producer::create(conf, errstr);
    delete conf;
    std::cout << "producer created using conf, conf deleted" << std::endl;

    RdKafka::Topic *topic = RdKafka::Topic::create(producer, topicName, nullptr, errstr);
    std::cout << "topic created using producer" << std::endl;

    for (std::string line; std::getline(std::cin, line);)
	{
		std::cout << line.c_str() << '\n';
        producer->produce(topic, RdKafka::Topic::PARTITION_UA,
                          RdKafka::Producer::RK_MSG_COPY /* Copy payload */,
                          const_cast<char *>(line.c_str()), line.size(),
                          nullptr, nullptr);
    }
    std::cout << "sendind loop exited" << std::endl;

    producer->flush(10*1000 /* wait for max 10 seconds */);

    delete topic;
    delete producer;

	return 0;
}
 
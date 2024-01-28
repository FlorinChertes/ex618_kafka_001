
#include <librdkafka/rdkafkacpp.h>

#include <iostream>
#include <string>


int main ([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
	std::cout << "main ex618_kafka_001" << std::endl;

	std::string errstr;

	std::string brokers = "localhost:9092";
    std::string topicName = "amazingTopic";

    RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    conf->set("bootstrap-server", brokers, errstr);

    RdKafka::Producer *producer = RdKafka::Producer::create(conf, errstr);
    delete conf;

    RdKafka::Topic *topic = RdKafka::Topic::create(producer, topicName, nullptr, errstr);

    for (std::string line; std::getline(std::cin, line);)
	{
		std::cout << line.c_str() << '\n';
        producer->produce(topic, RdKafka::Topic::PARTITION_UA,
                          RdKafka::Producer::RK_MSG_COPY /* Copy payload */,
                          const_cast<char *>(line.c_str()), line.size(),
                          nullptr, nullptr);
    }

    producer->flush(10*1000 /* wait for max 10 seconds */);

    delete topic;
    delete producer;

	return 0;
}
 
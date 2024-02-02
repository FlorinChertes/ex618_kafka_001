#ifdef _MSC_VER
#include <rdkafkacpp.h>
#elif __GNUC__
#include <librdkafka/rdkafkacpp.h>
#endif

#include <string>
#include <iostream>
#include <cassert>

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
 {
    std::cout << "kafka consumer" << std::endl;

    std::string errstr;
    std::string brokers = "localhost:9092";
    std::string topicName = "amazingTopic";
    std::string groupId = "testGroup";

    // Create a configuration object
    RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    conf->set("group.id", groupId, errstr);
    conf->set("metadata.broker.list", brokers, errstr);
    conf->set("enable.auto.commit", "true", errstr);

    // Create a consumer using the configuration
    RdKafka::Consumer *consumer = RdKafka::Consumer::create(conf, errstr);
    delete conf; // No longer need the configuration object

    // Create a topic object
    RdKafka::Topic *topic = RdKafka::Topic::create(consumer, topicName, nullptr, errstr);

    // Start the consumer
    consumer->start(topic, 0, RdKafka::Topic::OFFSET_END);

    std::cout << "Consuming messages from topic: " << topicName << std::endl;

    while (true) {
        // Poll for a message
        RdKafka::Message *msg = consumer->consume(topic, 0, 1000);
        
        // Check message status
        switch (msg->err()) {
            case RdKafka::ERR__TIMED_OUT:
                // No message received within the timeout period
                break;
            case RdKafka::ERR_NO_ERROR:
                // Valid message received
                std::cout << "Message received: " << std::string(static_cast<const char *>(msg->payload()), msg->len()) << std::endl;
                break;
            case RdKafka::ERR__PARTITION_EOF:
                // End of partition reached
                std::cout << "End of partition reached" << std::endl;
                break;
            default:
                // An error occurred
                std::cerr << "Consume error: " << msg->errstr() << std::endl;
                break;
        }

        delete msg; // Free up the message object
    }

    // Stop the consumer
    consumer->stop(topic, 0);

    // Clean up
    delete topic;
    delete consumer;

    return 0;


}

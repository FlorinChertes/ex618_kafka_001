#include <rdkafka.h>

#include <vector>
#include <string>

#include <iostream>
#include <cassert>

int main ([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
	std::cout << "kafka consumer" << std::endl;

    const char* version = rd_kafka_version_str();
    std::cout << "librdkafka version: " << version << std::endl;

    std::string brokers{ "localhost:9092" };
    const std::string topicName{ "amazingTopic" };
    std::string groupId{ "testGroup" };

	std::cout << "input brocker address: " << std::endl;
    std::string brocker_address{};
    std::getline(std::cin, brocker_address);
    if (brocker_address.empty() == false)
    {
      brokers =  brocker_address;
    }
    std::cout << "input brocker address: >" << brokers << "<" << std::endl;

    char errstr[512];

    rd_kafka_conf_t *conf = rd_kafka_conf_new();

    if (rd_kafka_conf_set(conf, "bootstrap.servers", brokers.c_str(),
        errstr, sizeof(errstr)) != RD_KAFKA_CONF_OK) {
        fprintf(stderr, "%% %s\n", errstr);
        exit(1);
    }

    if (rd_kafka_conf_set(conf, "group.id", groupId.c_str(),
        errstr, sizeof(errstr)) != RD_KAFKA_CONF_OK) {
        fprintf(stderr, "%% %s\n", errstr);
        exit(1);
    }

    rd_kafka_topic_conf_t* topic_conf = rd_kafka_topic_conf_new();

    if (rd_kafka_conf_res_t res = rd_kafka_topic_conf_set(topic_conf, "acks", "all",
        errstr, sizeof(errstr));
        res != RD_KAFKA_CONF_OK)
    {
        fprintf(stderr, "%% %s\n", errstr);
        exit(1);
    }

    if (rd_kafka_conf_set(conf, "debug", "broker,topic,msg",
        errstr, sizeof(errstr)) != RD_KAFKA_CONF_OK) {
        fprintf(stderr, "%% %s\n", errstr);
        exit(1);
    }

    size_t cnt;
    const char** dump = rd_kafka_conf_dump(conf, &cnt);
    for (size_t i = 0; i < cnt; i += 2) {
        std::cout << dump[i] << " = " << dump[i + 1] << std::endl;
    }
    rd_kafka_conf_dump_free(dump, cnt);


    /* Create Kafka consumer handle */
    rd_kafka_t* rk = rd_kafka_new(RD_KAFKA_CONSUMER, conf, errstr, sizeof(errstr));
    if ( rk == nullptr) {
        fprintf(stderr, "%% Failed to create new consumer: %s\n", errstr);
        exit(1);
    }

    const std::vector<std::string> topics{ topicName };
    rd_kafka_topic_partition_list_t* c_topics{ rd_kafka_topic_partition_list_new((int)topics.size()) };
    for (const auto& topic : topics)
    {
        rd_kafka_topic_partition_list_add(c_topics, topic.c_str(), RD_KAFKA_PARTITION_UA);
    }

    if (rd_kafka_resp_err_t err = rd_kafka_subscribe(rk, c_topics);
        err != RD_KAFKA_RESP_ERR_NO_ERROR)
    {
        fprintf(stderr, "%% Failed to start consuming topics: %s\n", rd_kafka_err2str(err));
        exit(1);
    }


    static const int MIN_COMMIT_COUNT = 1000;
    static int msg_count = 1;
    static const bool running = true;

    std::cout << "Enter loop " << std::endl;

    while (running) {
        rd_kafka_message_t* rkmessage = rd_kafka_consumer_poll(rk, 1500);
        if (!rkmessage)
            continue; // timeout: no message

        std::cout << "Message received: " <<
            std::string(static_cast<const char*>(rkmessage->payload), rkmessage->len) <<
            std::endl;

        rd_kafka_message_destroy(rkmessage);

        if ((++msg_count % MIN_COMMIT_COUNT) == 0)
        {
            if (rd_kafka_resp_err_t err = rd_kafka_commit(rk, nullptr, 0);
                err != RD_KAFKA_RESP_ERR_NO_ERROR) {
                // application-specific rollback of processed records
            }
            rd_kafka_commit(rk, nullptr, 0);
        }
    }


    if (rd_kafka_resp_err_t err = rd_kafka_consumer_close(rk);
        err != RD_KAFKA_RESP_ERR_NO_ERROR)
        fprintf(stderr, "%% Failed to close consumer: %s\n", rd_kafka_err2str(err));
    else
        fprintf(stderr, "%% Consumer closed\n");

	return 0;
}

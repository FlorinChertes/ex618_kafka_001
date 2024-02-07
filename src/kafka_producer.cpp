#ifdef _MSC_VER
#include <rdkafka.h>
#elif __GNUC__
#include <librdkafka/rdkafka.h>
#endif

#include "kafka_producer.h"

#include <vector>
#include <string>

#include <thread>
#include <chrono>

#include <iostream>
#include <cassert>

static constexpr int const DELAY_ms = 50;

void kafka_producer_send()
{

    const char* version = rd_kafka_version_str();
    std::cout << "librdkafka version: " << version << std::endl;

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

    char errstr[512];

    rd_kafka_conf_t *conf = rd_kafka_conf_new();

    if (rd_kafka_conf_set(conf, "bootstrap.servers", brokers.c_str(),
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

    /* Create Kafka producer handle */
    rd_kafka_t* rk = rd_kafka_new(RD_KAFKA_PRODUCER, conf,errstr, sizeof(errstr));
    if ( rk == nullptr) {
        fprintf(stderr, "%% Failed to create new producer: %s\n", errstr);
        rd_kafka_conf_destroy(conf);
        exit(1);
    }

    rd_kafka_topic_t* rkt = rd_kafka_topic_new(rk, topicName.c_str(), topic_conf);
    if (rkt == nullptr)
    {
        fprintf(stderr, "%% Failed to create new topic: %s\n", errstr);
        rd_kafka_topic_conf_destroy(topic_conf);
        exit(1);
    }

    for (std::string line; std::getline(std::cin, line);)
    {
        std::cout << line.c_str() << '\n';

        if (const int ret_val = rd_kafka_produce(rkt,
                                                RD_KAFKA_PARTITION_UA,
                                                RD_KAFKA_MSG_F_COPY,
                                                const_cast<char*>(line.c_str()), line.size(),
                                                nullptr, 0,
                                                nullptr);
            ret_val == -1)
        {
            fprintf(stderr, "%% Failed to produce to topic %s: %s\n",
                topicName.c_str(), rd_kafka_err2str(rd_kafka_last_error()));
        }
    }

    rd_kafka_topic_destroy(rkt);
    rd_kafka_destroy(rk);

    std::cout << "sendind loop exited" << std::endl;

}


void kafka_producer_send(const std::string& line)
{
    std::string brokers = "localhost:9092";
    const std::string topicName = "amazingTopic";

    char errstr[512];

    std::cout << "sending start" << std::endl;

    rd_kafka_conf_t* conf = rd_kafka_conf_new();
    assert(conf != nullptr);
    if (rd_kafka_conf_set(conf, "bootstrap.servers", brokers.c_str(),
        errstr, sizeof(errstr)) != RD_KAFKA_CONF_OK)
    {
        fprintf(stderr, "%% %s\n", errstr);
        exit(1);
    }

    if (rd_kafka_conf_set(conf, "debug", "broker,topic,msg",
        errstr, sizeof(errstr)) != RD_KAFKA_CONF_OK)
    {
        fprintf(stderr, "%% %s\n", errstr);
        exit(1);
    }

    rd_kafka_topic_conf_t* topic_conf = rd_kafka_topic_conf_new();
    assert(topic_conf != nullptr);
    if (rd_kafka_conf_res_t res = rd_kafka_topic_conf_set(topic_conf, "acks", "all",
        errstr, sizeof(errstr));
        res != RD_KAFKA_CONF_OK)
    {
        fprintf(stderr, "%% %s\n", errstr);
        exit(1);
    }


    /* Create Kafka producer handle */
    rd_kafka_t* rk = rd_kafka_new(RD_KAFKA_PRODUCER, conf, errstr, sizeof(errstr));
    if (rk == nullptr) {
        fprintf(stderr, "%% Failed to create new producer: %s\n", errstr);
        rd_kafka_conf_destroy(conf);
        exit(1);
    }

    rd_kafka_topic_t* rkt = rd_kafka_topic_new(rk, topicName.c_str(), topic_conf);
    if (rkt == nullptr)
    {
        fprintf(stderr, "%% Failed to create new topic: %s\n", errstr);
        rd_kafka_topic_conf_destroy(topic_conf);
        exit(1);
    }

    std::cout << line << '\n';

    if (const int ret_val = rd_kafka_produce(rkt,
        RD_KAFKA_PARTITION_UA,
        RD_KAFKA_MSG_F_COPY,
        const_cast<char*>(line.c_str()), line.size(),
        nullptr, 0,
        nullptr);
        ret_val == -1)
    {
        fprintf(stderr, "%% Failed to produce to topic %s: %s\n",
            topicName.c_str(),
            rd_kafka_err2str(rd_kafka_last_error()));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_ms));

    rd_kafka_topic_destroy(rkt);
    rd_kafka_destroy(rk);

    std::cout << "sending done" << std::endl;
}

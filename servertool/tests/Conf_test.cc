#include "Conf.h"

#include <limits>
#include <stdint.h>

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using basetool::string;

BOOST_AUTO_TEST_CASE(testConf)
{
	basetool::Conf conf("./test.ini");
	conf.put("node1.testint");
	conf.put("node1.testbool");
	conf.put("node1.testfloat");

	conf.put("node2.teststring");
	conf.put("node2.testuint32");
	conf.put("node2.testuint64");
	
	BOOST_CHECK_EQUAL(conf.get<int>("node1.testint"), 12345);
	BOOST_CHECK_EQUAL(conf.get<bool>("node1.testbool"), false);
	BOOST_CHECK_CLOSE_FRACTION(conf.get<float>("node1.testfloat"), 1.234567, 0.000001);
	BOOST_CHECK_EQUAL(conf.get<string>("node2.teststring"), "chenping");
	BOOST_CHECK_EQUAL(conf.get<uint32_t>("node2.testuint32"), 12345678);
	BOOST_CHECK_EQUAL(conf.get<uint64_t>("node2.testuint64"), 123456789098);
}


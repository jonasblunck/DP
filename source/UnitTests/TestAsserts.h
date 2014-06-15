
#pragma once

// 
// defines some simple ASSERT macros for unit testing
//

#define DPUNIT_STR_EQUAL(exp, was) if (exp != was) { s_unittest_success = false; printf("\r\n%s(%ld) : expected '%s' but got '%s'\r\n", __FILE__, __LINE__, exp, was); } else { printf("."); }
#define DPUNIT_INT_EQUAL(exp, was) if (exp != was) { s_unittest_success = false; printf("\r\n%s(%ld) : expected '%d' but got '%d'\r\n", __FILE__, __LINE__, exp, was); } else { printf("."); }
#define DPUNIT_EQUAL(exp, was) if (exp != was) { s_unittest_success = false; printf("\r\n%s(%ld) : '%s' and '%s' differs\r\n", __FILE__, __LINE__, #exp, #was); } else { printf("."); }
#define DPUNIT_ISTRUE(exp) if (false == (exp)) { s_unittest_success = false; printf("\r\n%s(%ld) : '%s' was false (expected true)\r\n", __FILE__, __LINE__, #exp); } else { printf("."); }
#define DPUNIT_ISNOTNULL(exp) if (NULL == exp) { s_unittest_success = false; printf("\r\n%s(%ld) : '%s' was NULL\r\n", __FILE__, __LINE__, #exp); } else { printf("."); }
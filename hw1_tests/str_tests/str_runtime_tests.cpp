//
// CS104 Str runtime tests
//

#include <str.h>

#include <gtest/gtest.h>

#include <functional>

#include <runtime_evaluator.h>
#include <random_generator.h>

// dummy function to call on an anonymous/temporary
// string to ensure compiler doesn't optimize away
// the passed string
void nopStr(const Str& s1)
{
  (void) s1;
}
TEST(StrRuntime, Concatenate)
{

	RuntimeEvaluator evaluator("Str::operator+()", 15, 25, 30, [&](uint64_t numElements, RandomSeed seed)
	{
	  char* inputStr = new char[numElements+1];
	  for(uint64_t i = 0; i < numElements; i++) inputStr[i] = 'a';
	  inputStr[numElements] = '\0';
	  Str s1(inputStr);
	  Str s2(inputStr);
	  
	  BenchmarkTimer timer;
	  Str s3(s1+s2);
	  timer.stop();
	  
	  return timer.getTime();
	});

	//evaluator.enableDebugging();
	evaluator.setCorrelationThreshold(1.4);
	evaluator.evaluate();

	EXPECT_TRUE(evaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LINEAR));
}


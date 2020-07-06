#include <twiteng.h>
#include <gtest/gtest.h>
#include <functional>
#include <runtime_evaluator.h>
#include <random_generator.h>
#include <vector>
#include <math.h>
#include <string>

using namespace std;

//global engines
vector<TwitEng*> engs;

void setupEngs()
{
	int num_tweets = 1024;
	for (int i = 0; i < 6; i++)
	{
		TwitEng* twit = new TwitEng();
		string f = "runtime_test_files/" + to_string(num_tweets) + "_5.dat";
		char filename[f.length()];
		strcpy(filename, f.c_str());
		twit->parse(filename);
		num_tweets *= 2;
		engs.push_back(twit);
	}
}

TEST(SearchRuntime, And)
{
	setupEngs();
	RuntimeEvaluator evaluator("AND", 10, 15, 30, [&](uint64_t numElements, RandomSeed seed)
	{
		int index = log2(numElements) - 10;
		TwitEng* t = engs[index];
		vector<string> search_terms;
		search_terms.push_back("a");
		search_terms.push_back("b");
		BenchmarkTimer timer;
		t->search(search_terms, 0);
		timer.stop();
		return timer.getTime();
	});

	evaluator.setCorrelationThreshold(1.4);
	evaluator.evaluate();
	EXPECT_TRUE(evaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LINEARITHMIC));
}

TEST(SearchRuntime, Or)
{
	setupEngs();
	RuntimeEvaluator evaluator("OR", 10, 15, 30, [&](uint64_t numElements, RandomSeed seed)
	{
		int index = log2(numElements) - 10;
		TwitEng* t = engs[index];
		vector<string> search_terms;
		search_terms.push_back("a");
		search_terms.push_back("b");
		BenchmarkTimer timer;
		t->search(search_terms, 1);
		timer.stop();
		return timer.getTime();
	});

	evaluator.setCorrelationThreshold(1.4);
	evaluator.evaluate();
	EXPECT_TRUE(evaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LINEARITHMIC));
}

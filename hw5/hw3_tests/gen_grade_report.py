#!/usr/bin/python3

import cs_grading
import cmake_problem
import setting
import os

source_dir = os.path.dirname(os.path.realpath(__file__))

RESULT_DIR = 'results/' # where test results are stored
GRADER_CONFIG = '../grader.txt'
RUBRIC_GENERAL = os.path.join(source_dir, 'rubric', 'general.config')
RUBRIC_USER = os.path.join(source_dir, 'rubric', 'user.config')
RUBRIC_TWEET = os.path.join(source_dir, 'rubric', 'tweet.config')
RUBRIC_DATETIME = os.path.join(source_dir, 'rubric', 'datetime.config')
RUBRIC_CMD_HANDLER = os.path.join(source_dir, 'rubric', 'cmd_handler.config')
RUBRIC_SEARCH = os.path.join(source_dir, 'rubric', 'search.config')
RUBRIC_TWITENG = os.path.join(source_dir, 'rubric', 'twiteng.config')
#RUBRIC_LOGIN = os.path.join(source_dir, 'rubric', 'login.config')
#RUBRIC_HEAP = os.path.join(source_dir, 'rubric', 'heap.config')
#RUBRIC_RECS = os.path.join(source_dir, 'rubric', 'recs.config')

GRADE_REPORT_DIR = './'

HOMEWORK = cs_grading.Homework(
    3,
    RESULT_DIR,
    False,
    detailed_results=setting.DETAILED_RESULT,
    compile_flags=setting.COMPILE_FLAGS,
    logging_level=setting.LOGGING_LEVEL,
)

#P1 = cs_grading.Problem(HOMEWORK, 1, 'login', 15)
#P2 = cs_grading.Problem(HOMEWORK, 2, 'heap', 25)
#P3 = cs_grading.Problem(HOMEWORK, 3, 'recs', 40)

P1 = cs_grading.Problem(HOMEWORK, 3.1, 'user', 6)
P2 = cs_grading.Problem(HOMEWORK, 3.2, 'tweet', 6)
P3 = cs_grading.Problem(HOMEWORK, 3.3, 'datetime', 5)
P4 = cs_grading.Problem(HOMEWORK, 3.4, 'cmd_handler', 14)
P5 = cs_grading.Problem(HOMEWORK, 3.5, 'search', 24)
P6 = cs_grading.Problem(HOMEWORK, 3.6, 'twiteng', 25)

for problem, rubric in [(P1, RUBRIC_USER), (P2, RUBRIC_TWEET), (P3, RUBRIC_DATETIME), (P4, RUBRIC_CMD_HANDLER), (P5, RUBRIC_SEARCH), (P6, RUBRIC_TWITENG)]:
    problem.generate_results(
        cmake_problem.cmake_problem,
        True,
        timeout=0,)
    if setting.GENERATE_GRADE_REPORT:
        problem.grade_problem(RUBRIC_GENERAL, rubric)
    if setting.OPEN_RESULT:
        problem.open_result(text_editor=setting.TEXT_EDITOR)


GRADER = cs_grading.Grader(GRADER_CONFIG, setting.LOGGING_LEVEL)
cs_grading.generate_grade_report(HOMEWORK, GRADER, GRADE_REPORT_DIR, overwrite=True, logging_level=setting.LOGGING_LEVEL)

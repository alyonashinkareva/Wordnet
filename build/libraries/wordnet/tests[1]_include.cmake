if(EXISTS "/Users/alyonashinkareva/Desktop/asss/wordnet-alyoshinkkaa/build/libraries/wordnet/tests[1]_tests.cmake")
  include("/Users/alyonashinkareva/Desktop/asss/wordnet-alyoshinkkaa/build/libraries/wordnet/tests[1]_tests.cmake")
else()
  add_test(tests_NOT_BUILT tests_NOT_BUILT)
endif()

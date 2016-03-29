#Finite State Machine

##Team Members

* Jiabin Xiang
* Xiaotian Zhang
* Pengpeng Ge
* Rafael Bezerra

The tasks that each member will be doing will still be defined as at this moment the system is still being modeled.


##Proposal
The goals of this project are [1] to develop a regex stack-based grammar parser that can receive patterns, validate them and create a state machine that will [2] search for string patterns with a complexity of O(n).

In order to get the complexity as low as O(n) a data structure based on tries will be used. An array of pointers will be used to access a linked list that represents the sentence which the pattern will be matched against.

##Testing
The code will be tested on many standard patterns using a set of sentences. The following items will be evaluated:

1. The regex correctness: the code shall parse the regex and inform if any error is encountered
2. The search correctness: the code shall inform whether the pattern exists in the sentence or not.

The code will also be benchmarked against the default regex library.
# 45-minutes overview
1 minute - RAII concept
4 minutes - RAII multi-thread
2.5 minutes - PIMPL
2.5 minutes - Rule of five
5 minutes - RTTI

5 minutes - copy & swap, connstexpr, consteval
5 minutes - Object Pooling
5 minutes - small object optimization
5 minutes - return value optimization

15 minutes - projects

Other idioms:
- construct on fist use https://wiki.sei.cmu.edu/confluence/pages/viewpage.action?pageId=88046492
- erase-remove idiom https://wiki.sei.cmu.edu/confluence/display/cplusplus/EXP63-CPP.+Do+not+rely+on+the+value+of+a+moved-from+object


C idioms:
- lstat-fopen-fstat idiom https://wiki.sei.cmu.edu/confluence/display/c/FIO32-C.+Do+not+perform+operations+on+devices+that+are+only+appropriate+for+files
- arr[sizeof(arr)/sizeof(arr[0])]) idiom 
    - https://wiki.sei.cmu.edu/confluence/display/c/ARR39-C.+Do+not+add+or+subtract+a+scaled+integer+to+a+pointer
    - https://wiki.sei.cmu.edu/confluence/display/c/ARR01-C.+Do+not+apply+the+sizeof+operator+to+a+pointer+when+taking+the+size+of+an+array
- reallocating memory idiom https://wiki.sei.cmu.edu/confluence/display/c/MEM04-C.+Beware+of+zero-length+allocations

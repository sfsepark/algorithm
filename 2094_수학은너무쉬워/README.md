https://www.acmicpc.net/problem/2904

# 사용한 std 자료구조 
std::set 
http://www.cplusplus.com/reference/set/set/
- 사용한 메서드 : insert , begin , end

std::unordered_map
http://www.cplusplus.com/reference/unordered_map/unordered_map/?kw=unordered_map
- 사용한 메서드 : find, begin , end 

# 접근 방식
각 숫자를 소인수분해한 뒤에 각 숫자가 몇개의 소수로 이루어져있는지 저장한다(bucket).

동시에 전체 숫자에 총 몇개의 소수가 있는지 저장한다(totalBucket)

totalBucket에서 각 소수가 몇개 존재하는지 파악한 후, 각 숫자에 몇 개의 소수를 나눠줬을 때 최대 score를 만족할 수 있는지

판단하여 move 값을 지정한다.

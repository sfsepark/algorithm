divide and conqure 문제.

문자열(std::string)을 이용하여 접근했다.

# 고생한 점

입력받을 때 std::cin의 >> operator를 사용하려했는데, 이 operator는 개행문자까지의 모든 문자를 읽어들이므로 주의가 필요하다.

시험 환경을 미리 알아두면 좋을거같다.

g++ Main.cc -o Main -O2 -Wall -lm -static -std=gnu++14 -DONLINE_JUDGE -DBOJ

를 이용해서 로컬에서 못잡아낸 런타임에러를 잡아냄
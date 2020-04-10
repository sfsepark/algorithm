https://juggernaut.tistory.com/entry/%ED%8D%BC%EC%A7%80-%EB%AC%B8%EC%9E%90%EC%97%B4-%EA%B2%80%EC%83%89Fuzzy-string-search

레벤슈타인의 편집거리 알고리즘을 응용해서 풀예정

문제에서 편집을 할 수 있는 경우의 수는 a , d , m 이 있다.

a,d,m에 의해서 현재 문자열을 완성할수 있는지 각각 확인하고

a,d,m으로 수정된 문자 이외의 부분은 미리 구해놓은 편집거리를 기반으로 DP 테이블을 채워나가면된다.
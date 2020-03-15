https://www.acmicpc.net/problem/2250

접근 방식 : 

x값을 1씩 늘려가며 중위탐색으로 이진트리를 순회하면서 각 레벨의 너비를 구하려했으나..

실수 : 

노드의 번호가 뒤죽박죽 들어올 수 있다는 것까지는 파악했으나

루트노드가 당연히 1번이라고 오해하여 문제를 잘 못 읽음.

실제로는 루트노드를 구해야하는데..

루트 노드를 구하는 방법 :

disjoint-set을 이용한 union-find 알고리즘 ( https://gmlwjd9405.github.io/2018/08/31/algorithm-union-find.html )
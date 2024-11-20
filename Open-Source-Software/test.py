import numpy as np
import pandas as pd
from scipy.optimize import minimize

# 1. 데이터 불러오기
data = pd.read_csv("circle.csv", header=None)
points = data.values  # 10개의 점 좌표 (x, y)


# 거리 계산 함수 정의
def compute_distance_squared(a, b, r, x, y):
    # 원의 중심 (a, b)와 반지름 r
    distance_squared = 0  # 총 거리를 저장할 변수

    for xi, yi in zip(x, y):
        if abs(xi - a) <= r:  # Blue 영역 (원의 x 좌표에 해당)
            dist_sq = abs(yi - b)  # 수직 거리
        elif abs(yi - b) <= r:  # Green 영역 (원의 y 좌표, x 범위 제외)
            dist_sq = abs(xi - a)  # 수평 거리
        else:  # Red 영역
            dist_sq = 100  # 고정 거리 제곱 (100의 제곱)

        # 거리 제곱을 누적하여 합산
        distance_squared += dist_sq

    return distance_squared

# 3. 최적화 함수 정의
def objective(params):
    a, b, r = params  # 원의 파라미터 (a, b, r)
    return compute_distance_squared(a, b, r, points[:, 0], points[:, 1])


# 4. 최적화 실행: 초기값 (a=0, b=0, r=1)
initial_guess = (0, 0, 1)
result = minimize(objective, initial_guess, bounds=[(-10000, 10000), (-10000, 10000), (0.1, 100)])

# 최적의 파라미터 (a, b, r) 출력
a_opt, b_opt, r_opt = result.x
print(f"Optimal parameters: a = {a_opt:.3f}, b = {b_opt:.3f}, r = {r_opt:.3f}")
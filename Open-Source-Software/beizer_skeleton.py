import numpy as np
import matplotlib.pyplot as plt


def select_ctrl_pts(x, y, theta, x_goal, y_goal, theta_goal, s1=1, s2=1):
    '''Select control points based on start and goal positions and orientations'''

    # 시작점과 목표점
    P0 = np.array([x, y])  # 시작점
    P3 = np.array([x_goal, y_goal])  # 목표점

    # 현재 각도와 목표 각도에 따른 방향 벡터 계산
    # 제어점의 모양을 부드럽게 조정하기 위해 직각 방향 벡터 사용
    # s1, s2는 곡선의 형태를 조정하는 스케일 값
    P1 = P0 + s1 * np.array([np.cos(theta), np.sin(theta)])  # 제어점 1
    P2 = P3 - s2 * np.array([np.cos(theta_goal), np.sin(theta_goal)])  # 제어점 2

    return P0, P1, P2, P3


def generate_cubic_bezier_curve(P0, P1, P2, P3, steps=100):
    '''Generate cubic Bezier curve based on control points'''
    t = np.linspace(0, 1, steps).reshape(-1, 1)
    return (1 - t) ** 3 * P0 + 3 * (1 - t) ** 2 * t * P1 + 3 * (1 - t) * t ** 2 * P2 + t ** 3 * P3


def visualize_cubic_bezier_curve(P0, P1, P2, P3, steps=100):
    '''Visualize a cubic Bezier curve and its control points'''
    curve = generate_cubic_bezier_curve(P0, P1, P2, P3, steps)

    # 베지어 곡선 그리기
    plt.plot(curve[:, 0], curve[:, 1], color='blue', label='Cubic Bezier Curve', lw=2)

    # 제어점 연결선 그리기
    plt.plot([P0[0], P1[0]], [P0[1], P1[1]], 'g--', label='P0-P1', lw=2)
    plt.plot([P2[0], P3[0]], [P2[1], P3[1]], 'r--', label='P2-P3', lw=2)

    # 제어점을 굵은 점으로 표시
    plt.scatter([P0[0], P1[0], P2[0], P3[0]], [P0[1], P1[1], P2[1], P3[1]],
                color=['green', 'green', 'red', 'red'], s=100, zorder=5)

    # 축 라벨, 그리드, 비율 설정
    plt.xlabel('x')
    plt.ylabel('y')
    plt.grid(True)
    plt.gca().set_aspect('equal', adjustable='box')  # 비율을 동일하게 설정
    plt.xlim(0,6)
    plt.ylim(0,6)

    # 범례 추가
    plt.legend()

    # 그래프 출력
    plt.show()


# 테스트 케이스 정의
x, y, theta = 1, 2, np.pi / 4  # 시작 위치
x_goal, y_goal, theta_goal = 3, 4, -np.pi / 4  # 목표 위치
s1, s2 = 1, 2

# 제어점 생성
P0, P1, P2, P3 = select_ctrl_pts(x, y, theta, x_goal, y_goal, theta_goal, s1, s2)
print(f'제어점: P0 = {P0}, P1 = {P1}, P2 = {P2}, P3 = {P3}')

# 3차 베지어 곡선 시각화
visualize_cubic_bezier_curve(P0, P1, P2, P3)
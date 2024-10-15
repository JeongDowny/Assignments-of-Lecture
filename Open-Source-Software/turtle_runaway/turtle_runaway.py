# This example is not working in Spyder directly (F5 or Run)
# Please type '!python turtle_runaway.py' on IPython console in your Spyder.
import tkinter as tk
import turtle
import time 
import math

class RunawayGame:
    def __init__(self, canvas, runner, chaser, catch_radius=30):
        self.canvas = canvas
        self.runner = runner
        self.chaser = chaser
        self.catch_radius2 = catch_radius**2

        # Initialize 'runner' and 'chaser'
        self.runner.shape("police_turtle.gif")
        self.runner.color('blue')
        self.runner.penup()

        self.chaser.shape("crime_turtle.gif")
        self.chaser.color('red')
        self.chaser.penup()

        # Instantiate an another turtle for drawing
        self.drawer = turtle.RawTurtle(canvas)
        self.drawer.hideturtle()
        self.drawer.penup()

    def is_catched(self):
        p = self.runner.pos()
        q = self.chaser.pos()
        dx, dy = p[0] - q[0], p[1] - q[1]
        return dx**2 + dy**2 < self.catch_radius2

    def start(self, init_dist=400, ai_timer_msec=600):
        self.runner.setpos((-init_dist / 2, 0))
        self.runner.setheading(0)
        self.chaser.setpos((+init_dist / 2, 0))
        self.chaser.setheading(180)

        # TODO) You can do something here and follows.
        self.starttime = time.time()
        self.ai_timer_msec = ai_timer_msec
        self.score = 0

        self.drawer.penup()
        self.drawer.setpos(0, 20)
        text = "당신은 희대의 범죄를 일으킨 거북이입니다.\n경찰 거북이를 피해 도망가십시오!\n5초 버틸때마다 점수와 난이도가 올라갑니다.\n'Sacpe bar'를 눌러 시작하세요."
        self.drawer.write(text, align="center", font=("Arial", 15, "normal"))
        
        self.canvas.onkeypress(lambda: self.step(), 'space')

    def step(self):
        self.runner.run_ai(self.chaser.pos(), self.chaser.heading())
        self.chaser.run_ai(self.runner.pos(), self.runner.heading())

        # TODO) You can do something here and follows.
        is_catched = self.is_catched()
        self.nowtime = time.time()
        self.time = self.nowtime - self.starttime
        new_score = self.time//10
        
        if new_score > self.score:
            self.score = new_score
            self.ai_timer_msec -= 50

        self.drawer.clear()

        if is_catched:
            self.drawer.setpos(0, 0)
            self.drawer.penup()
            self.drawer.write(f'Final Score: {self.score:.0f}', align="center", font=("Arial", 30, "normal"))
            return

        self.drawer.setpos(-300, 300)
        self.drawer.write(f'Time: {self.time:.0f} Score: {self.score:.0f}', font=("Arial", 10, "normal"))

        # Note) The following line should be the last of this function to keep the game playing
        self.canvas.ontimer(self.step, int(self.ai_timer_msec))

class ManualMover(turtle.RawTurtle):
    def __init__(self, canvas, step_move=10, step_turn=10):
        super().__init__(canvas)
        self.step_move = step_move
        self.step_turn = step_turn

        # Register event handlers
        canvas.onkeypress(lambda: self.forward(self.step_move), 'Up')
        canvas.onkeypress(lambda: self.backward(self.step_move), 'Down')
        canvas.onkeypress(lambda: self.left(self.step_turn), 'Left')
        canvas.onkeypress(lambda: self.right(self.step_turn), 'Right')
        canvas.listen()

    def run_ai(self, opp_pos, opp_heading):
        pass
            

class RandomMover(turtle.RawTurtle):
    def __init__(self, canvas, step_move=10, step_turn=10):
        super().__init__(canvas)
        self.step_move = step_move
        self.step_turn = step_turn

    def run_ai(self, opp_pos, opp_heading):
        runner_pos = self.pos()
        chaser_pos = opp_pos

        dx = chaser_pos[0] - runner_pos[0]
        dy = chaser_pos[1] - runner_pos[1]
        angle = math.degrees(math.atan2(dy, dx))

        self.setheading(angle)
        self.forward(self.step_move)


if __name__ == '__main__':
    # Use 'TurtleScreen' instead of 'Screen' to prevent an exception from the singleton 'Screen'
    root = tk.Tk()
    root.title("Turle Runaway")
    canvas = tk.Canvas(root, width=700, height=700)
    canvas.pack()
    #message = tk.Message(root, text="당신은 용왕의 신하인 거북아입니다. 용왕을 살리기 위해 토끼의 간을 가져다 바쳐야 합니다. 100초 안에 토끼 10마리를 잡지 못하면 용왕은 크게 실망할 것 입니다.")
    #message.pack()
    screen = turtle.TurtleScreen(canvas)
    screen.addshape("crime_turtle.gif")
    screen.addshape("police_turtle.gif")

    # TODO) Change the follows to your turtle if necessary
    runner = RandomMover(screen)
    chaser = ManualMover(screen)

    game = RunawayGame(screen, runner, chaser)
    game.start()
    screen.mainloop()
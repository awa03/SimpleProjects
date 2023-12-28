import tkinter as tk

currPlayer = 'X'
board = [[' ' for _ in range(3)] for _ in range(3)]  # Initialize an empty 3x3 board

def change_player_icon():
    global currPlayer
    if currPlayer == 'X':
        currPlayer = 'O'
    else:
        currPlayer = 'X'

def place_x(event):
    global board
    clicked_canvas = event.widget
    row, col = int(clicked_canvas.grid_info()["row"]), int(clicked_canvas.grid_info()["column"])

    if board[row][col] == ' ':
        board[row][col] = currPlayer
        clicked_canvas.create_text(50, 50, text=currPlayer, font=("Helvetica", 24), tags=currPlayer)
        if check_winner():
            show_winner(currPlayer)
            root.destroy()  # Close the Tkinter window on win
        else:
            change_player_icon()

def check_winner():
    global board
    # Check rows, columns, and diagonals for a win
    for i in range(3):
        if board[i][0] == board[i][1] == board[i][2] != ' ' or \
           board[0][i] == board[1][i] == board[2][i] != ' ':
            print("Player 1: X wins")
            return True

    if board[0][0] == board[1][1] == board[2][2] != ' ' or \
       board[0][2] == board[1][1] == board[2][0] != ' ':
        print("Player 2: O wins")
        return True


    return False

def show_winner(winner):
    winner_label.config(text=f"Player {winner} wins!")

def create_grid():
    global root, winner_label
    root = tk.Tk()
    root.title("Tic-Tac-Toe")

    winner_label = tk.Label(root, text="", font=("Helvetica", 16))
    winner_label.grid(row=3, column=0, columnspan=3)

    for i in range(3):
        for j in range(3):
            square = tk.Canvas(root, width=100, height=100, borderwidth=1, relief="solid")
            square.grid(row=i, column=j)
            square.bind("<Button-1>", place_x)

    root.mainloop()

create_grid()

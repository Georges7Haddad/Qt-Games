I implemented a simple desktop app using C++ in Qt.
In this project, a user is able to signup, login and play as guest. There are two games available: Kill Covid and Reversi(Othello).
Note that my main goal in this project was to become familiar with Qt and implement working games; the design can be enhanced.
# Accounts Management
## Login Page
You can login using your username and password or play as a guest. If you're not yet registered you can go to the signup page.
 
## Signup Page
You can signup by providing the mandatory fields specified by a star "*". You can also add a profile picture. We also check that the mail is valid as well as the password. All information are stored in json files.
 
## Welcome Page
We welcome you while displaying your username and profile picture. You can also start one of the two games. We also show the highscore for each game as well as your personel best in case you already played the game before.

# Game 1: Kill Covid
You're a doctor that can move across the map using the arrow keys and shoot projectiles represented by masks and pills using space.
The game ends when you lose all your lives or when you hit to exact required score(only for non-infinite modes). 
The screen is automatically scrolling up as you can notice with the background color changing. 
The game starts at a certain x speed depending on the game mode. If you kill 5 viruses it becomes 2x and if you kill more than 10, it becomes 4x.
You lose a life when you get hit by a virus or when it leaves the bottom of the sceen.
Your score increases when you hit a virus with a projectile, which then become smashed.
Your score and number of lives are dsiplayed at the top left of the screen and gets upadted while playing.
For finite games modes, your goal will appear at the top left at the beginning of the game.
When you start the game, you get redirected to a new screen where you're given four modes: easy, medium, hard and inifinite. For the easy, medium, and hard levels, you have to get to the exact required number of points to win. So, in case you got more points than required, your score won't increase because you need to hit the exact number. In the inifinite mode, you get the speed of the medium mode and keep playing until you lose, the higher the score the better.
There are 3 viruses sizes. Of course, hitting a smaller one, gives you more points.
When a game ends you get redirected to a new screen which tells you if you lost or won also displaying your score. If you got a new personal best it congratulates you and update it in your profile. If it is also a new game best, it congratulates you and updates it in the game json file.

Don't forget to turn on your speakers for some cool sound effects!
# Game 2: Reversi(Othello)
This is the classic game reversi also known as Othello. It is a strategy board game for two players, played on an 8×8 uncheckered board. 
Each player has a color, and the aim of the game is to get more of your pieces on the board than the opponent's pieces. Players take turns placing disks on the board. During a play, any disks of the opponent's color that are in a straight line and bounded by the disk just placed and another disk of the current player's color are turned over to the current player's color. That works vertically, horizontally and diagonally. I also added a feature to have a global timer for each player. Depending on the difficulty you choose, each player is going to have 7, 15 or 30 minutes to play all their moves. When your turn starts, your timer starts and when your turn ends, the timer stops. If you run out of time, you lose the game.

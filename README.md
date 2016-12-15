# Chutes-And-Ladder-HackerRank
This folder contains the source files I used for my attempt to solve a problem raised in a HackerRank problem. My main tool was CodeBlocks using C++

This was my first fully finished attempt, except this one, I do implement basic exception handling. The algorithm that I used could be best be described as a <a href="https://en.wikipedia.org/wiki/Distance-vector_routing_protocol">distance-vector</a> application in the context of well, a normal chutes and ladder game, where each roll you choose the best tile (out of the following 6) to go to, depending on whether they have chutes or ladders. Another type of algorithm that could work could be a <a href="https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm">djikstra-esque</a> approach, since before playing, the goal(reach tile 100) and the best and worst and ladders and chutes to traverse are already known beforehand.

Also to note, the algorithm that I have been using so far has generated correct output from the samples given in the hacker rank case, and reasonably correct output in other test case I ran.

One note though, I have not yet fully commented and documented all my code but that will be coming soon and there are a couple more exception cases to handle as well as the djikstra approach but I'll add that later in different branches.

Link to the full hackerRank problem <a href="https://www.hackerrank.com/challenges/the-quickest-way-up">here</a> for you to give a shot!

# rubiks

note to the Engineering Champ:

- there are two solutions to the rubik's cube challenge:
    - the first (mark 1) was my intuitive and initial attempt, using a large map of rotating fields, I was able to put together a data structure and algorithm to fulfill the basic requirements. My opinion of this solution is that it is simple to implement, simpler to understand, and a bit larger on the mapping.
    - the second (mark 2) was a result of thinking a bit about our conversation and some of the ideas you communicated to me. I think this solution will be a bit familiar to you. My opinion of this solution is that is is more complex, reduces the map size by a bit, but ultimately has to pay it back later when considering the changing orientation of the cublets. It also occurred to me that a vectorized implementation may end up much cleaner.

### build instructions
- clone repo
- make new directory "build/"
- cmake ..
- make

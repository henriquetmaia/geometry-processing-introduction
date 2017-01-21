htm2104, assignment 0:

Took me a bit to get started on what the right way to get the edges was, but then I just figured
I would not care about performance and go for a big hash of sets.

Simple enough, by only adding edges from lower vert index to higher vert index you can get rid
of duplicates (unordered edges will result).

This gives a result, which is hard to know if it is right.

Then for the Euler characteristic, you already have F and E, you just need V.
To get V, simply keep a vector of flags (0 or 1) for verts and go through 
either F or E to fill it. I go through F, setting V[i] to 1 if I see the vert.

Then you can sum that vector for the num of Verts. Chi = V - E + F.
I tested on the bunny and got 2, and the torus and got 0, and so I was satisfied to submit.

Everything was clear, although it took me a bit to figure out what the edges function was asking for.
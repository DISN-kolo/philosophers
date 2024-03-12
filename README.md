# philosophers
42's philosophers task

# don't forget
to turn in your assignment, place everything inside of the philo/ dir INSIDE of your repo dir. repo/philo/\<contents\>.

# what differs from oceano's tutorial/code along
we don't have the exit function. also, no error checks should be done on lock/unlock cuz like it's literally impossible 
(well, ALMOST) for us to have an error there that we can meaningfully process. furthermore some code parts can't even 
handle the error properly -- like the start\_routine. also, printf now prints with correct timings -- for that,
you have to gettime AFTER you mutex_locked in the 'write' part of the code.

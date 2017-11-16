Program Description: The driver program initializes the objects by calling the constructors with their respective
conditions to create each specific cache. Then it takes the instruction and address from the
input file and passes each into the simulate functions called on each object created. The driver
then prints out the total cache hits and accesses for each object.
The DirectMapped class creates a cache by using a private vector and pushing back a block
struct based on the cache size divided by the line size. Its simulate instruction gets the index by
shifting by the block bits modded by the size of the cache, and it gets the tag bits by shifting by
the block bits and the index bits. It then checks the cache at the index and checks if its valid and
if its tag equals the new tag, if so it increments the cache hits. If not, it replaces the tag and
makes the valid bit true if it was empty.
The SetAssociative class creates its cache by creating a temporary row and pushing back block
structs equal to the number of ways given and then pushes back the row onto the private vector.
It gets its index and tag the same way as the DirectMapped. Its direct simulate with LRU goes to
the spot in the cache indicated with the index bits and checks that whole row, and if it finds an
empty spot, it puts the tag in and updates its timestamp. If the valid block is true and the tag is
the same, it updates the cache hits and its timestamp. If the cache row wasn’t empty and it did
not hit, it replaces the spot with the lowest timestamp at the index. The simulate with no
allocation on a write miss works the same was as the simulate with LRU except that it does not
write to the cache if the instruction is a ‘Store’ and it does not replace if the ’Store’ misses. The
simulate with Next-Line Perfecting calls simulate with LRU and stores the current cache hits. It
then calls simulate with LRU again with the address + the block size so that its the next block
from the address. It then makes the current cache the previous cache. The simulate on Prefect
on a Miss stores the old cache, calls the simulate with LRU, and only calls simulate with LRU
again if the address missed or got put into the cache via replacement or because it had empty
spots.
The FullyAssociative class creates its cache the same way the DirectMapped creates its cache.
Since its fully associative, it does not need any index, so its tag is the address shifted by the
block size. The simulate with LRU checks the whole cache for the current tag and if it doesn’t
find it, it puts it in the first empty spot it sees. If everything is full, it searches for the spot with the
lowest timestamp to replace in the same way as SetAssociative. Its simulate with hot/cold uses
a tree structure to manage the hot/cold bits and decide where everything goes. All the node
structs initially start with everything at 0 (or false) and its node pointers at null. It then creates a
tree in the constructor based on how many levels needed with the levels being equal to the log
of the cache size divided by the block size plus 1. For our project, the levels needed are 10.
Then, in the simulate hot/cold function, it sets foundInCache equal to false and it only gets
updated if the tag is found, if not it calls the function to find the coldest spot and replaces that
spot with the new tag. Inside the findInCacheAndMaybeUpdate function, it searches each side
of the tree until it finds the node with the current tag its looking for. Along the way it changes the
hot/cold bits to true and false depending on the side it went down. If it does not find it in the
cache the findColdestReplaceAndUpdate function gets called. It finds which side of the current
pointer is cold and goes down to that node and calls itself again until it finds the leaf node which
it replaces the tag and updates the valid bit. Along the way, it updates the hot/cold bits.

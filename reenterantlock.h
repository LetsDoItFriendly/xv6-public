struct reenterantlock {
	int counter;
    uint locked;       // Is the lock held?
  	struct spinlock lk; // spinlock protecting this reenterant lock

  	// For debugging:
  	char *name;        // Name of lock.
  	int pid;           // Process holding lock
};
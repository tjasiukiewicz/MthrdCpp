
// PSEUDO CODE!!!

std::atomic<int> a{12};

std::atomic<int> b{13};

//a *= 12;
--a;

a.load(12, std::memory_order::memory_order_acquire);

struct X {
	int a;
	int b;
};

std::atomic<X> myXAtom;

int expected = 12;

std::atomic<int> a;
a.load(32);
while (not a.compare_exchange_strong(&expected, 90, m1, m2) ); // Oczekiwanie aż nie zapiszę 90


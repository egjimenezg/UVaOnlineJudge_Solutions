import math

def build_sieve(size):
  sieve_size = int(size + 1)
  sieve = [1] * sieve_size
  primes = []
  sieve[0], sieve[1] = 0, 0

  for i in range(4, sieve_size, 2):
    sieve[i] = 0

  upper_bound = int(math.sqrt(sieve_size))
  for number in range(2, upper_bound):
    if sieve[number]:
      for multiple in range(number*number, sieve_size, number):
        sieve[multiple] = 0
      primes.append(number)

  return primes, sieve

def find_and_print_odd_primes(n, primes, sieve):
  index = 0

  while index < len(primes) and primes[index] < n:
    a = primes[index]
    b = n - a
    if sieve[b]:
      return [a,b]
    index += 1
  return None

if __name__ == "__main__":
  primes, sieve = build_sieve(10e5)

  while n := int(input()):
    odd_primes = find_and_print_odd_primes(n, primes, sieve)
    if odd_primes is None:
      print("Goldbach's conjecture is wrong.")
    else:
      [a, b] = odd_primes
      print(f"{n} = {a} + {b}")


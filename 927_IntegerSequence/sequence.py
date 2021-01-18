cases = int(input())

def get_polynomic_term(coefficients, n):
  sum = 0

  for i in range(len(coefficients)):
    sum += coefficients[i]*(n**i)

  return sum

while cases > 0:
  polynomial = list(map(int, input().split()))
  d = int(input())
  k = int(input())

  coefficients = polynomial[1:]
  n = 1
  terms = d;

  while k > terms:
    n += 1
    terms += n*d

  print(get_polynomic_term(coefficients, n))
  cases -= 1


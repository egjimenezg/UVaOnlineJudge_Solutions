import math

case = 1

while True:
  roads, numbers = map(int, input().split())

  if numbers == 0 and roads == 0:
    break;

  suffixes = 0
  difference = roads - numbers

  suffixes = math.ceil(difference/numbers)

  if suffixes > 26:
    print(f'Case {case}: impossible')
  else:
    print(f'Case {case}: {suffixes}')

  case += 1

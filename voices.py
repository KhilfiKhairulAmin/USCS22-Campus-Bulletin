import sys
from bs4 import BeautifulSoup
import requests

def scrap():

  requests.

  bs = BeautifulSoup()

if __name__ == "__main__":
  for line in sys.stdin:
    p = line.strip()  # Read URL from stdin
    id, text = p.split('$', 1)
    text = text.replace('$', '\n')

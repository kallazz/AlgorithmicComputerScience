#!/bin/bash

trap "rm image.jpg" EXIT
# Cat image
curl -s https://api.thecatapi.com/v1/images/search?mime_types=jpg | jq -r '.[0].url' | xargs curl -s -o image.jpg
catimg -w 150 image.jpg

# Chuck Norris quote
curl -s https://api.chucknorris.io/jokes/random | jq '.value'

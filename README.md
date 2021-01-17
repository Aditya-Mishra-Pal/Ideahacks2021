# Ideahacks2021
My Project for IdeaHacks 2021(Jan 16 - Jan 17)
## Inspiration
My family and I enjoy gardening. Over the years, we have gotten busier and we neglect our tasks in the backyard such as watering the plants or covering them with cloth when it's too cold.
Additionally, I am very interested in the long term effects of soil health after gardening for so many years and watching this video: https://www.youtube.com/watch?v=EAO1A6EdVVA

My project has the unique ability to be able to help home gardeners keep their plants as healthy as possible (by notifying them when the temperature is too hot/cold or when the soil is too dry) and save them a lot of money in the long run. This can be done by checking if the soil is too wet and notifying the user if that is the case. Ideally this will also save money on home growers for buying compost and fertilizer (next section)

###Long Term Goal
For most plants, Nitrogen is what allows them to grow healthier (for instance, most fertilizer is primarily nitrogen).
According to a couple papers I have read, the rate at which moisture is lost from the soil is dependent on a couple of factors, most notably microbe content and nitrogen levels.
Currently, a soil sample examination costs at least $1200 and go to upwards of $5000. That test is recommended once every few years and for a home grower, that is a substantial cost.

From this I got to thinking that maybe it would be possible to estimate microbial content and nitrogen content in the soil based on the rate at which moisture is lost from the water. So in the long run my idea was to graph all the variables I have collected to see if there is any correlation and determine if we can estimate important aspects of the soil and analyze trends over time. (i.e, if humidity is higher, soil loses content faster)

https://extension.umn.edu/nitrogen/understanding-nitrogen-soils#nitrification-761161


## What it does
Provides User instant access to information pertinent to the health of their plants
Ensures Maximal Plant Health
Records Long-Term Weather/Moisture Information to analyze trends in the long run
Reminds User if they forget to water/shield the plants in specific circumstances.

## How we built it
SQL database PHP, C++, etc.
## Challenges we ran into
Never done databases, had lots of issues fixed it

## Accomplishments that we're proud of
I made a webserver!

## What we learned
Better idea of how servers and websites work
## What's next for SmartGarden
Make graphing capability stronger. Currently only maps against time.
Make Website look better, currently using a CSS script I found online, modified it for my data but it can look better
Email Bug(I am locked out of my Gmail account for sending too many emails)
Have it run on Server not on my Network
Have Graphs show up on my website as opposed to ThingSpeak
Do more powerful computation on Matlab to see if I can determine any correlation between variables

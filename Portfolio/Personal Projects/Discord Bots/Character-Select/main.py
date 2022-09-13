import discord
import os
import sys
from replit import db
import random
import asyncio
from keep_alive import keep_alive


def main(): #Inits discord bot info, commands, and role list
  TOKEN = db['TOKEN']
  intents = discord.Intents().all()
  intents.reactions = True
  client = discord.Client(intents=intents)
  role_count = 105
  command_list = [0]*role_count
  role_list = [0]*role_count

  @client.event
  async def on_ready(): #Upon startup, initialize the commands and roles from the respective files
    commands = open("command_list.txt", 'r')
    i = 0
    for line in commands:
      command_list[i] = line
      if command_list[i][len(command_list[i])-1] == '\n':
        command_list[i] = command_list[i][0:len(command_list[i])-1]
      i+=1
    commands.close()

    roles = open("role_list.txt", 'r')
    i = 0
    for line in roles:
      role_list[i] = line
      if role_list[i][len(role_list[i])-1] == '\n':
        role_list[i] = role_list[i][0:len(role_list[i])-1]
      i+=1
    roles.close()

    print("{0.user}".format(client))
    
  @client.event
  async def on_message(message):
    prefix = '!'
    if message.author == client.user:
     return

    #Prints list of role commands
    elif message.content.startswith(prefix+"roles"):
        infile = open('message.txt', 'r')
        file_contents = infile.read()
        infile.close()
        await message.channel.send(file_contents)

    #If '!' is part of the message but does not fit any of the conditions above, search through all possible role commands
    elif message.content.startswith(prefix):
      i = 0
      role_name = ""
      while i < role_count-1:
        if command_list[i] != 0:#If the current element is not an empty slot
          if message.content.endswith(prefix+command_list[i]) or message.content.endswith(prefix+command_list[i]+"_remove"):
            
            role_name = role_list[i]
            guild = message.author.guild

            if message.content.endswith("_remove"): #if '_remove' is appended to the end of the command, remove the respective role
              await message.author.remove_roles(discord.utils.get(guild.roles,name=role_name))

            else: #Add the role
              await message.author.add_roles(discord.utils.get(guild.roles,name=role_name))

            i = role_count #Break out of the loop

          else: #Increment index by 1
            i+=1

        else: #Break out of loop
          i = role_count  
  
  keep_alive() #Pings the bot
  client.run(TOKEN) #Activates the bot on discord
main()
import discord
import os
import ffmpeg
import random
import nacl
import asyncio
from keep_alive import keep_alive


def main():
  #tracemalloc.start()
  TOKEN = os.environ['TOKEN']
  intents = discord.Intents().all()
  client = discord.Client(intents=intents)


  @client.event
  async def on_ready(): #Upon startup
    print("{0.user}".format(client))

 # @client.event
  #async def on_voice_state_update(member, before, after):
  #  print(member)
  #  print(before)
  #  print(after)
  #  channel = None
  #  guild = member.guild #Constant for the guild
  #  bot_mem = guild.get_member(user_id=844475919372779530)
    #print("Before: "+bot_mem.voice.channel)
  #  if (((member.nick == bot_mem.nick and member.nick != None)) or (member.name == bot_mem.nick)) and after.channel != None:
  #    channel = after.channel
   #   vc = await channel.connect()
    #  print(after.channel)

  @client.event
  async def on_message(message):
    prefix = '?' #sets the stored prefix to check for
    guild = message.author.guild #Constant for the guild
    bot_mem = guild.get_member(user_id=844475919372779530) #Constant for the bot membership


    if message.author == client.user: #Prevents the bot from issuing commands to itself
     return

    if (((message.author.nick == bot_mem.nick and message.author.nick != None)) or (message.author.name == bot_mem.nick)) and not message.content.startswith(prefix): #If bot changed into a user, copy anything they say
      await message.channel.send(message.content)



    if message.content.startswith(prefix+'transform'):
      msg = message.content
      if checkParameter(msg, 'transform', prefix): #If no target entered
        await message.channel.send("Ditto used transform...but it has no target!")

      else:
        start = (14,13)
        i = 0
        while i < 2:
          name = ""
          name = message.content
          name = name[start[i]:len(name)-1]
          member = guild.get_member(user_id=int(name))
          print(name)
          if member != None:
            i = 2
          else:
            i += 1
        
        try:
          if member != None and member != bot_mem: #If a user has been found
            await member.avatar_url_as(static_format='png').save(fp="pfp.png")
            fp = open("pfp.png", 'rb')
            pfp = fp.read()
            fp.close()
            await client.user.edit(avatar=pfp)

            cur_roles = bot_mem.roles
            i = len(cur_roles)-1
            while i > 0:
              try:
                if cur_roles[i].name != "Ditto":
                  await bot_mem.remove_roles(bot_mem.roles[i])
              except:
                print(None)
              i -= 1

            i = 1
            while i < len(member.roles):
              try:
                await bot_mem.add_roles(member.roles[i])
              except:
                print(None)
              i+=1

            if member.nick == None:
              await bot_mem.edit(nick=member.name)
            else:
              await bot_mem.edit(nick=member.nick)

            await message.channel.send("Ditto transformed into "+member.nick+"!")

          elif member == bot_mem: #If the bot is selected, revert back
            fp = open("132.png", 'rb')
            pfp = fp.read()
            fp.close()
            await client.user.edit(avatar=pfp)

            cur_roles = bot_mem.roles
            i = len(cur_roles)-1
            while i > 0:
              try:
                if cur_roles[i].name != "Ditto":
                  await bot_mem.remove_roles(bot_mem.roles[i])
              except:
                  print(None)
              i -= 1
            
            await bot_mem.edit(nick=None)
            await message.channel.send("Ditto reverted back!")

          else:
              await message.channel.send("Ditto used transform...but it failed!")
        except:
            await message.channel.send("Ditto is too tired to transform. It'll recover in a few minutes...")


  keep_alive()
  client.run(TOKEN)

def checkParameter(msg, command, prefix): #If the command has a parameter, check if parameter is empty
  if msg.endswith(' ') or msg == prefix+command:
    return True
  else:
    return False

main()
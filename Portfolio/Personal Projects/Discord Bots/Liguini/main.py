import discord
from discord.ext import commands
import os
import random
import ffmpeg
import nacl
import asyncio
from keep_alive import keep_alive
import img_sch.google_images_download.google_images_download
import youtube_dl
vc = "" #current VC the bot is in
repeat = False #flag if the bot should repeat music or not
song_counter = 0 #counts how many songs are left in the bot's queue
song_info = [0]*100 #Array of extracted song links
debug = False #flag if the bot should show more detailed error messages
prefix = '~' #command prefix
client = commands.Bot(command_prefix = prefix)
skip_song = False

#os.system('youtube-dl --rm-cache-dir')
ydl_opts = { #specifies options for the youtube player
    'format': 'bestaudio/best',
    'extract_flat': True, 
    'skip_download': True,
    'simulate': True,
    'postprocessors': [{
        'key': 'FFmpegExtractAudio',
        'preferredcodec': 'mp3',
        'preferredquality': '192',
    }]
}


def main():

  #Confirms bot is up
  @client.event
  async def on_ready(): #Upon startup
    print("o ye, {0.user} time".format(client))
  
  #Error handling function
  @client.event
  async def on_command_error(ctx, error):
    global debug
    if isinstance(error, commands.MissingRequiredArgument):
      if ctx.message.content.startswith(prefix+"pick"):
        await ctx.channel.send("you-a need at least-a two options for-a me to pick")
      elif ctx.message.content.startswith(prefix+"ini"):
        await ctx.channel.send("you-a need to specify a user to-a ini-fy")
      elif ctx.message.content.startswith(prefix+"sing"):
        await ctx.channel.send("you forgot-a the link")

    if isinstance(error, commands.CommandInvokeError):
      if not str(error).find("ClientException"):
        if str(error).find("AttributeError"):
          if ctx.message.content.startswith(prefix+"talk") or ctx.message.content.startswith(prefix+"sing"):
            name = name_finder(ctx)
            await ctx.message.channel.send("i cant-a join vc if you not-a in vc or if im-a already in-a vc, "+name)
  
          if ctx.message.content.startswith(prefix+"leave"):
            name = name_finder(ctx)
            await ctx.message.channel.send("i'm-a not in-a vc you're-a in, "+name) 
        else:      
          await ctx.channel.send("i could-a not understand the command")

    if isinstance(error, commands.MemberNotFound):
        await ctx.channel.send("i-a could not-a find-a the specified paisano")

    if debug == True:
      await ctx.channel.send("```DEBUG: "+str(error)+"```")
  
  #Bot says hello
  @client.command()
  async def hello(ctx):
    if str(ctx.author) == "AND0R#5605":
      await ctx.channel.send('ciao, papa mia')
    else:
          if ctx.author.nick == None:
            name = ctx.author.name
          else:
            name = ctx.author.nick
          await ctx.channel.send("ciao, "+name)
  
  #Picks between two options
  @client.command()
  async def pick(ctx, choice1, choice2):
    fail_chance = 5
    random.seed()
    fail = random.randrange(1, 100, 1)
    if fail <= fail_chance:
      await ctx.channel.send("ono, i-a can't decide...")
    elif fail > fail_chance:
      random.seed()
      selection = random.randint(1,2)
      if selection == 1:
        selected_op = choice1
      elif selection == 2:
        selected_op = choice2
      await ctx.channel.send("i'm-a gonna pick **"+selected_op+"**")

  #Sends a reaction image depending on command. 
  #If current_mood, send random reaction.
  @client.command(aliases=["praise", "berate", "plank"])
  async def current_mood(ctx):
    reactions = ["praise", "berate", "plank"]
    if(ctx.message.content.startswith(prefix+"current_mood")):
      random.seed()
      print("hit1")
      selected_emote = random.randrange(1, 3)
      emote = reaction(reactions[selected_emote])
      await ctx.channel.send(file=discord.File(emote))
    else:
      selected_emote = ctx.message.content[1:len(ctx.message.content)]
      print(selected_emote)
      emote = reaction(selected_emote)
      await ctx.channel.send(file=discord.File(emote))

  #Append 'ini' to the end of user's name in server
  @client.command()
  async def ini(ctx, target):
    name = int(ctx.message.content[7:len(ctx.message.content)-1])
    print(name)
    guild = ctx.message.author.guild

    member = await guild.fetch_member(name)
    print(member)

    if member != None:
      if member.nick == None:
        await member.edit(nick=member.name+'ini')
      else:
        await member.edit(nick=member.nick+'ini')
        await ctx.channel.send("name has-a been updated")
    else:
        await ctx.channel.send("no-a valid user has-a been entered")

  #Toggles debug mode to show more details for certain errors
  @client.command()
  async def debug(ctx):
    if str(ctx.author) == "AND0R#5605":
      global debug
      debug = not debug
      await ctx.channel.send("debug mode set to-a **"+str(debug)+"**")
      
    else:
      await ctx.channel.send("you not-a my papa")    

  #Liguini joins and speaks in vc
  @client.command()
  async def talk(ctx):
    channel = ctx.message.author.voice.channel
    vc = await channel.connect()
    random.seed()
    selection = random.randrange(1, 9)
    gib = 'l_gib/gib_'+str(selection)+'.wav'
    vc.play(discord.FFmpegPCMAudio(gib))
    while vc.is_playing():
      await asyncio.sleep(1)
    await vc.disconnect()

  #Liguini leaves vc and clears the music list
  @client.command()
  async def leave(ctx):
      global song_info
      global song_counter
      await vc.disconnect()
      for i in range(song_counter):
        song_info[i] = 0
      song_counter = 0


  #Toggles song repeating
  @client.command()
  async def repeat(ctx):
    global repeat
    repeat = not repeat
    await ctx.message.channel.send("music repeat set to-a: **"+str(repeat)+"**")

  #Adds music to song queue, and also has skip functionality
  @client.command()
  async def sing(ctx, link):
    global song_info
    global repeat
    global song_counter
    global vc
    global skip_song
    playing = False
#    link = link[6:len(link)]
    print(link)
    if link.find("list") != -1:
      await ctx.message.channel.send("im-a sorry, i do not-a support playlists for now")
    else:
      channel = ctx.message.author.voice.channel
      if link.find("skip") != -1:
        print("hit1")
        skip_song = True
      else:
        print("hit2")
        with youtube_dl.YoutubeDL(ydl_opts) as ydl:
          song_info[song_counter] = ydl.extract_info(link, download=False)
        song_counter += 1
        print(song_counter)
      vc = await channel.connect()
#Check this later
      if not vc.is_playing():
              #vc = await channel.connect()
        while song_info[0] != 0:
          playing = True
          while playing == True:
            vc.play(discord.FFmpegPCMAudio(song_info[0]["formats"][0]["url"]))
            while vc.is_playing():
              if skip_song == True:
                vc.stop()
              else:
                await asyncio.sleep(1)
            if repeat != True or skip_song == True:
              playing = False
              skip_song = False

          for i in range(song_counter):
              song_info[i]=song_info[i+1]
          song_counter -= 1
          print(song_counter)
          
        await vc.disconnect()
            
      else:
          await ctx.message.channel.send("song is-a added to the queue")

  keep_alive() 
  client.run('OTc5OTY3MTQ4MTU3OTkyOTYw.GK5sN_.nqYL6Y66ogMPoZOmOxE6dMaZI3VkiP8y_F1168')

  
#********************************************************************************************************
def imageURL(q_list): #Format the query list and search for a url
  i = 0
  limit = 100
  while i < len(q_list):
    if i == 0:
      query = q_list[i]
      i += 1
    else:
      query = query + "," + q_list[i]
      i += 1
  response = img_sch.google_images_download.google_images_download.googleimagesdownload()
  arguments = {"keywords" : query, "limit" : limit, "no_download":True, "silent_mode":True}
  url_list = response.download(arguments)
  random.seed()
  selection = random.randrange(0, limit-1)
  q_selection = random.randrange(0, len(q_list)-1)
  url = url_list[0][q_list[q_selection]][selection]
  return url

def reaction(action):
  random.seed()
  max_images = 5
  formats = ['.gif', '.png', '.jpg', '.jpeg']
  selection = random.randrange(1, max_images+1)
  print(selection)
  img_path = 'luigi_react/'+action+'/'+str(selection)
  index = 0
  while index < len(formats):
    if os.path.isfile(img_path+formats[index]):
      return img_path+formats[index]
    else:
      index += 1

def name_finder(ctx):
  if ctx.message.author.nick == None:
    name = ctx.message.author.name
  else:
    name = ctx.message.author.nick

  return name

main()
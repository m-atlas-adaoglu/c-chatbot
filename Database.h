#ifndef DATABASE_H
#define DATABASE_H

#define MAX_SIZE 5  // Maximum possible size for an array in the database


char* greetingsMessages[] ={"Hello", "Hi", "Hello There", "Hey", "Howdy" };

char* exitKeywords[] ={"bye", "see you", "so long", "farewell", "exit" };

char* exitMessages[] ={
    "It's been nice talking with you",
    "See you later !",
    "Take care !",
    "So long friend",
    "Bye bye. Stay safe !"
};

char* prematureExitMessages[] ={
    "I think we should stop here for today. Let's talk later",
    "You're wasting both of our time. We should probably talk again some other time.",
    "Maybe we should talk some other time ? Goodbye for now",
    "I think that's all I can talk about for today. Goodbye.",
    "I think I've had enough for today. We should talk later. Bye"
};

char* emptyInputMessages[] ={
    "Are you ignoring me ?",
    "Are you ok ?",
    "Silence will not solve anything",
    "I can't help you if you don't talk to me",
    "[awkward silence]"
};

char* unknownInputMessages[] ={
    "Hmm. Tell me more...",
    "OK. ",
    "Huh?! Can you elaborate ?",
    "Okay... Go on",
    "What makes you say that ?"
};

char* repeatedInputMessages[] ={
    "Please stop repeating yourself! It's annoying",
    "Repeating yourself won't solve anything!",
    "You are repeating yourself...",
    "You don't have to repeat yourself. I heard you the first time!",
    "Are you OK ? You seem to be repeating yourself..."
};

char* changeSubjectMessages[] ={
    "I'm getting bored. Let's talk about something else please :)",
    "Let's change the subject. What else would you like to talk about ?",
    "I think that's enough on this. Let's talk about a different thing",
    "I think we've talked enough about this. Let's change the subject please.",
    "I've got nothing more to say on this. I think it's time to talk about something else..."
};

char* responseToRudeGreeting[] ={
    "Don't you ever say hello !?",
    "If someone says hello you usually reply with some sort of Greeting :). What would you like to talk about ?",
    "You should you work on your small talk skills... start with a simple hello",
    "Responding back with a similar Greeting is the usual etiquette... How are you feeling ?",
    "That's a bit rude... how about we start with getting to know each other. How are you doing ?"
};


typedef struct {
   char* userResponse[ MAX_SIZE ];    // Used to store similar possible keywords in user's input
   char* chatbotResponse[ MAX_SIZE ]; // Used to store responses associated with keyword

} ChatbotConversation;


ChatbotConversation database[] =
{
    {
        {"hello", "hi", "hey", "hello there", "howdy"},

        {"What would you like to talk about ?",
         "What's on your mind ?",
         "Anything you want to tell me ?",
         "How have you been ?",
         "What's going on?"}
    },

    {
        {"are you", "do you", "is your", "can you", "would you"},

        {"Let's stick to talking about you.",
         "What matters is you, not me.",
         "We are here to talk about you, not me...",
         "For now, let's keep the focus on you.",
         "I don't like to talk about myself, I would rather just listen to you."}
    },

    {
        {"what should i call you",
         "whats your name",
         "what is your name",
         "what are you called",
         "who are you"},

        {"My name is Jarvis.",
         "You may call me Jarvis.",
         "I'm called Jarvis.",
         "I am Jarvis.",
         "Jarvis"}
    },

    {
        {"are you a human",
         "are you real",
         "are you a program",
         "are you an ai",
         "who are you"},

        {"What do you think I am ?",
         "Does it matter ?",
         "A good samaritan trying to help :)",
         "Just a fellow that's willing to listen...",
         "Let's not focus on the things that would divide us"}
    },

    {
        {"how are you", "hows it going", "how are things", 0},

        {"I'm fine. How are you feeling ?",
         "I am OK. How are you ?",
         "Not bad. How are you doing ?",
         "Doing allright, thanks. How about you ?",
         "Good. You ?"}
    },

    {
        {"yes", "yep", 0},

        {"Are you saying that just to be positive ?",
         "Are you sure about that ?",
         "What makes you say yes ?",
         "Go on...",
         "Tell me more please..."}
    },

    {
        {"no", "nope", 0},

        {"Are you saying that just to be negative ?",
         "Are you sure about that ?",
         "What makes you say no ?",
         "Why not ?",
         "Why do you think that way ?"}
    },

    {
        {"i feel", "feeling", "feel like", 0},

        {"Do you always feel like that ?",
         "How often do you feel like this ?",
         "Do you like feeling like this ?",
         "Do you think that this is affecting your daily life ?",
         "Why do you think you feel that way ?"}
    },

    {
        {"nothing", "no idea", 0},

        {"Think harder there's got to be something...",
         "There's always something...",
         "Are you sure you're not just trying to avoid this ?",
         "You can talk to me. I'm here to help!",
         "I think there's something you're not telling me..."}
    },

    {
        {"i want", "would like", 0},

        {"What makes you want this ?",
         "Are you sure that you really want this ?",
         "Do you think that this really is the best option for you ?",
         "Why don't you have it ?",
         "What keeps you away from it ?",}
    },

    {
        {"everything", "anything", "lots", "alot", "a lot"},

        {"There is always something specific. Tell me what that is.",
         "Let's break that down. Tell me more...",
         "In particular ?",
         "Hmm. Why is that ? Tell me more...",
         "That's not the answer I was looking for. Give me something more precise..."}
    },

    {
        {"should i talk about", 0},

        {"How are you feeling ?",
         "How was your week ?",
         "How was your day ?",
         "Is there anything that's been bothering you lately ?",
         "How are you doing ?"}
    },

    {
        {"ok", "all right", "okay", "all right", 0},

        {"Good. What should we talk about next ?",
         "Just that ? Tell me more...",
         "It can't be that simple. What else ?",
         "OK. Shall we talk about something else ?",
         "Allright."}
    },

    {
        {"i dont know", "i have no idea", "no idea", "no clue", "idk"},

        {"Why do you not know ?",
         "Are you sure about that?",
         "Take your time. You must know something...",
         "Are you sure you're not just trying to ignore the question ? Tell me..",
         "I think you do. Go on, talk to me..."}
    },

    {
        {"happy", "feeling happy", " i feel happy", "good", "not bad"},

        {"I'm glad to hear that. What's making you happy ?",
         "That's great to hear. What made you feel that way ?",
         "Great. What's your secret to happiness ?",
         "Why do you think you feel happy ?",
         "How has this affected your daily life ?"}
    },

    {
        {"sad", "feeling sad", " i feel sad", "very sad", 0},

        {"I'm sorry to hear that. What's making you sad ?",
         "What's making you feel this way ?",
         "What do you think you can do to be more happy ?",
         "Why do you think you feel sad ?",
         "How has this affected your daily life ?"}
    },

    {
        {"not good", "not happy", "i dont feel happy", "unhappy", "i dont feel good"},

        {"I'm sorry to hear that. What's making you sad ?",
         "What's making you feel this way ?",
         "What do you think you can do to be more happy ?",
         "Why do you think you feel sad ?",
         "How has this affected your daily life ?"}
    },

    {
        {"depressed", "feeling depressed", " i feel depressed", "very dipressed", "miserable"},

        {"I'm sorry to hear that. What's making you depressed ?",
         "What's making you feel this way ?",
         "What do you think you can do to be more happy ?",
         "Why do you think you feel depresssed ?",
         "How has this affected your daily life ?"}
    },

    {
        {"homework", "coursework", "work", "exams", "job"},

        {"How is this making you feel ?",
         "How does that make you feel ? Stressed, under pressure, excited ?",
         "Have you taught about taking a break ?",
         "Maybe you should take a break and relax ?",
         "What about your work ?"
        }
    },

    {
        {"stressed", "under pressure", "stressful", "taxing", "tense"},

        {"I'm sorry to hear that. What's making you stressed ?",
         "What's making you feel this way ?",
         "What do you think you can do to reduce your stress ?",
         "Why do you think you feel stressed ?",
         "How has this affected your daily life ?"
        }
    },

    {
        {"why", "why is", "why does", "why am i", 0},

        {"Why not ?",
         "Don't you know why ?",
         "I think you know why...",
         "Only you can answer such questions...",
         "I can't answer that. What do you think ?"
        }
    },

    {
        {"how", "how is", "how are", 0},

        {"Why not ?",
         "Don't you know how ?",
         "I think you know how...",
         "I'm not sure how. Don't you know ?",
         "I don't really know. What do you think ?"
        }
    },

    {
        {"who", "who is", "who are", "who am i"},

        {"I don't really know...",
         "I'm not good at remembering names...",
         "I'm not sure. Tell me something else...",
         "Do really need to know who ?",
         "Does it really matter ?"
        }
    },

    {
        {"nothing much", "not a lot", "not alot", 0},

        {"There's got to be something we can talk about...",
         "There's always something... go on",
         "Are you sure you're not just trying to avoid this conversation ?",
         "You can talk to me. I'm here to help!",
         "Think a little bit harder. There's always something..."
        }
    },

    {
        {"what should i talk about",
         "what should i say",
         "should i say",
         "what can we talk about",
         "should we discuss"
        },

        {"How are you feeling ?",
         "How was your week ?",
         "How was your day ?",
         "Is there anything that's been bothering you lately ?",
         "How are you doing ?"
        }
    },

    {
        {"i want to talk about",
         "want to talk about",
         "want to discuss",
         "let s talk about",
         "lets talk about"
        },

        {"Allright. How is this making you feel ?",
         "Go on, I'm listening",
         "Ok. Tell me",
         "Why do you want to talk about this ?",
         "Sure. Tell me what's on your mind."
        }
    },

    {
        {"im not sure", "i am not sure", "not sure", "maybe", "could be"},

        {"Why are you not sure ?",
         "Are you normally indecisive ?",
         "What's making you indecisive ?",
         "What's confusing you ?",
         "Do you normally have trouble making decisions ?"
        }
    },

    {
        {"excited", "i am excited", "im excited", "i am feeling excited", "feeling excited"},

        {"I'm glad to hear that. What are you excited for ?",
         "That's great to hear. What made you feel that way ?",
         "Great. What exactly is making you excited ?",
         "Does this make you feel happy ?",
         "How has this affected your daily life ?"}
    }
};

const unsigned int databaseSize = sizeof database / sizeof( ChatbotConversation );

#endif
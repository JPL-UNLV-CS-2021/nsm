import xml.etree.ElementTree as ET
import csv
from lxml import etree
import json
import sys, getopt
#<startState>
#LINE 1 <state_name> -> <string>
#LINE 2 <state_parent> -> <string>
#LINE 3 <entry_functions> -> <action>
#LINE 4 <exit_functions> -> <action>
#LINE 5 <state_transitions> -> <event>/<newState>/<action>,
#LINE 6 <initialTransition> -> <newState>
#LINE 7 <junctions> -> <EVENT>/<CONDITION>/<IFSTATE>/<IFACTION>/<ELSESTATE>/<ELSEACTION>

class State:
    def __init__(self, sn, level, s):
        self.stateName = sn    
        self.stateParent = ""
        self.entryFunctions = []
        self.exitFunctions = []
        self.transitions = []
        self.initialTransition = {}
        self.junction = {}
        self.level = 0
        self.parent = None
        self.children = []
        self.xmlNode = s
        
    def setParent(self, p, s):
        self.stateParent = p
        self.parent = s


class Var:
    def __init__(self, n, t, v, p):
        self.name = n
        self.type = t
        self.visibility = v
        self.properties = p

    
    
    
defaultState = {}
states = {}
vars = []
files = {}
stateLevel = 0

def visitStatechart(sc):
    global defaultState
    defaultState = sc[0]
    
    for i in range(1, len(sc)):
        visitChildren(sc[i])
        
def visitTransition(t, so):

    transition = {
        "trigger":"",
        "target":"",
        "action":"",
    }
    
    junction = {
        "trigger":"",
        "action":"",
        "guard": "",
        "iftarget": "",
        "ifaction": "",
        "elsetarget": "",
        "elseaction": "",
    }
    
    #if theres no target on transition then it must be a junction
    if "target" in t.attrib.keys():
        transition["trigger"] = t.attrib["trig"]
        transition["target"] = t.attrib["target"]
        
        if t.findall("action"):
            transition["action"] = t.findall("action")[0].text.strip()
            
        so.transitions.append(transition)
    else:
        junction["trigger"] = t.attrib["trig"]
        
        if t.findall("action"):
            junction["action"] = t.findall("action")[0].text.strip()
            
        
        choices = t.findall("choice")
        if choices:
            junction["iftarget"] = choices[0].attrib["target"]
            
            guard = choices[0].find("guard")
            if guard != None:
                junction["guard"] = guard.text.strip()
            else:
                junction["guard"] = choices[1].find("guard").text.strip()
                
                
            if choices[0].findall("action"):
                junction["ifaction"] = choices[0].findall("action")[0].text.strip()
                
            junction["elsetarget"] = choices[1].attrib["target"]
            
            if choices[1].findall("action"):
                junction["elseaction"] = choices[1].findall("action")[0].text.strip()
        
        so.junction = junction

    

def visitState(s):
    global states
    global stateLevel
    so = State(s.attrib['name'],stateLevel, s)
    stateLevel += 1
    for k in s:
        if k.tag == "state":
            child = visitState(k)
            child.setParent(s.attrib['name'],s)
            states[child.stateName] = child
            so.children.append(child)
        if k.tag == "entry":
            so.entryFunctions = so.entryFunctions + k.text.split("\n")    
        if k.tag == "exit":
            so.exitFunctions = so.exitFunctions + k.text.split("\n")
        if k.tag == "tran":
            visitTransition(k, so)
            #so.transitions.append(k.attrib)
        if k.tag == "initial":
            so.initialTransition["target"] = k.attrib["target"]
    stateLevel -= 1
    return so
    
def visitFile(node):
    global files
    
    files[node.attrib["name"]] = node.find("./text").text
    

def visitChildren(node):
    
    global states
    
    if node.tag == "statechart":
        visitStatechart(node)
        
    if node.tag == "state":
        s = visitState(node)
        s.setParent("Null", None)
        states[s.stateName] = s
        
    if node.tag == "attribute":
        v = Var(node.attrib["name"],
                node.attrib["type"],
                node.attrib["visibility"],
                node.attrib["properties"])
        vars.append(v)
        
    if node.tag == "file":
        visitFile(node)
    
        

    if node.tag == "package" or node.tag == "class" or node.tag == "directory":
        for i in range(len(node)):
            visitChildren(node[i])
        

def parseXML(xmlfile):
  
    # create element tree object
    tree = ET.parse(xmlfile)
  
    # get root element
    root = tree.getroot()
  
    # create empty list for news items
    newsitems = []
  
    # iterate news items
    
    for i in range(len(root)):
        visitChildren(root[i])
    

    # for state in states:
        
        # for t in state.transitions:
            # t["target"] = getTarget(t["target"], root, state.stateName, state)
            

        
    # return news items list
    return newsitems
    

def getTarget(path, root, startingName, s):
    coor = []
    
    if path == "..":
        return startingName
        
    # while '../' in path:
        # path = path[3:]
        # s = s.find('./')
        # print(s)

    for i in range(len(path)):
        if path[i].isdigit():
            coor.append(int(path[i]))
            
    currEle = root.find(".//statechart")

    for i in range(len(coor)):
        currEle = (currEle[coor[i]])
    
    answer = path
    if currEle != root.find(".//statechart"):
        answer = currEle.attrib["name"]

    return answer


def main():
    global states
    global files
    
    
    try:
        xmlfile = sys.argv[1]
    except IndexError:
        print("This program requires lxml parser to be installed.")
        print("Usage:")
        print ("\tparser.py <inputfile>")
        sys.exit(2)
        
    # parse xml file
    newsitems = parseXML(xmlfile)
    
    # create element tree object
    tree = etree.parse(xmlfile)
  
    # get root element
    root = tree.getroot()
    
    #resolve transition targets
    for s in states:
        for t in states[s].transitions:
        
            path = t["target"]
            
            
            if path == "..":
                t["target"] = states[s].stateName
            else:
                
                #first set xml parser to current state tran element
                
                
                
                currEle = root.find('.//state[@name="'+states[s].stateName+'"]/tran[@target="' + t["target"] + '"]')
                while '../' in path:
                

                    currEle = next(currEle.iterancestors())
                    path = path[3:]
                    
                if path == '..':
                    t["target"] = currEle.attrib["name"]
                else:
                    #path should have only numerical values at this point 
                    coordinates = path.split('/')
                    
                    for x in coordinates:
                        l =  currEle.getchildren()
                        currEle = l[int(x)]
                        t["target"] = currEle.attrib["name"]
                        
    

    
    #Resolve Default State target
    path = defaultState.attrib["target"]
    path = path[3:]
    coordinates = path.split('/')
    tree = etree.parse(xmlfile)
    root = tree.getroot()
    currEle = root.find(".//statechart")
    for x in coordinates:
        l =  currEle.getchildren()
        currEle = l[int(x)]
        defaultState.attrib["target"] = currEle.attrib["name"]


    #Resolve initial transition targets
    
    for s in states:
        if(len(states[s].initialTransition) != 0):
                path = states[s].initialTransition["target"]
                currEle = root.find('.//state[@name="'+states[s].stateName+'"]/initial[@target="' + path + '"]')
                
                while '../' in path:
                    currEle = next(currEle.iterancestors())
                    path = path[3:]
                    
                coordinates = path.split('/')
                
                for x in coordinates:
                    l =  currEle.getchildren()
                    if states[s].entryFunctions != []:
                        currEle = l[int(x)+1]
                    else:
                        currEle = l[int(x)]
                    states[s].initialTransition["target"] = currEle.attrib["name"]


    #Resolve Junction Targets

    for s in states:
        if(len(states[s].junction) != 0):
                ifpath = states[s].junction["iftarget"]
                elsepath = states[s].junction["elsetarget"]
                
                path = ifpath
                
                if path == '..':
                    s.junction["iftarget"] = currEle.attrib["name"]
                else:
                    currEle = root.find('.//state[@name="'+states[s].stateName+'"]/tran[@trig="' + states[s].junction["trigger"] + '"]')
                    l = currEle.getchildren()
                    
                    #set to if portion
                    currEle = currEle.find('.//choice[@target="' +  path + '"]')

                
                    while '../' in path:
                        currEle = next(currEle.iterancestors())
                        path = path[3:]
                    
                    if path == '..':
                        states[s].junction["iftarget"] = currEle.attrib["name"]
                    else:
                    
                        coordinates = path.split('/')
                            
                        for x in coordinates:
                            children =  currEle.getchildren()
                            l = []
                            for child in children:
                                if child.tag != "entry":
                                    l.append(child)
                            currEle = l[int(x)]
                            
                        states[s].junction["iftarget"] = currEle.attrib["name"]
                            
                            
                path = elsepath
                
                if path == '..':
                    states[s].junction["elsetarget"] = currEle.attrib["name"]
                else:
                    currEle = root.find('.//state[@name="'+states[s].stateName+'"]/tran[@trig="' + states[s].junction["trigger"] + '"]')
                    l = currEle.getchildren()
                    
                    #set to if portion
                    currEle = currEle.find('.//choice[@target="' +  path + '"]')

                
                    while '../' in path:
                        currEle = next(currEle.iterancestors())
                        path = path[3:]
                    
                    if path == '..':
                        
                        currEle = next(currEle.iterancestors())
                        states[s].junction["elsetarget"] = currEle.attrib["name"]
                    else:
                    
                        coordinates = path.split('/')
                        for x in coordinates:
                            children =  currEle.getchildren()
                            l = []
                            for child in children:
                                if child.tag != "entry":
                                    l.append(child)
                                    
                            currEle = l[int(x)]
                            
                        states[s].junction["elsetarget"] = currEle.attrib["name"]
    
    
    
    
    #Now we need to resolve inital transitions
    #for each transition and junction
    #check if target is a node with initial transition
    #if it is then follow the chain of inital transitions to a leaf node
    
    
    for s in states:
    
        #first do it for transitions
        for t in states[s].transitions:
            targetState = states[t["target"]]
            while 'target' in targetState.initialTransition:
                targetState = states[targetState.initialTransition['target']]
            
            t["target"] = targetState.stateName
                    
        #now for the junction
        
        j = states[s].junction
        if 'iftarget' in j:
            targetState = states[j["iftarget"]] 
            while 'target' in targetState.initialTransition:
                targetState = states[targetState.initialTransition['target']]
            
            j["iftarget"] = targetState.stateName 
            
        if 'elsetarget' in j:
            targetState = states[j["elsetarget"]]
            while 'target' in targetState.initialTransition:
                targetState = states[targetState.initialTransition['target']]
            
            j["elsetarget"] = targetState.stateName 
            
    
    
    #lastly we need to generate the path for the default state
    initialPath = [defaultState.attrib['target']]
    targetState = states[defaultState.attrib['target']]
    while 'target' in targetState.initialTransition:
        targetState = states[targetState.initialTransition['target']]
        initialPath.append(targetState.stateName)
    
    defaultState.attrib['target'] = targetState.stateName
    
    #lets also make a list of all events
    masterTransList = []
    for s in states:
        for t in states[s].transitions:
            if t["trigger"]:
                if t["trigger"] not in masterTransList:
                    masterTransList.append(t["trigger"])
                
        if 'trigger' in states[s].junction:
            masterTransList.append(states[s].junction['trigger'])
            

    
    #wrap in JSON
    
    jsonDump = {}
    jsonDump['initialPath'] = initialPath 
    
    
    jsonDump['variables'] = []
    for v in vars:
        jsonDump['variables'].append({
            'name': v.name,
            'type': v.type,
            'visibility': v.visibility,
            'properties': v.properties
        })
        
    jsonDump['states'] = []
    for s in states:
        jsonDump['states'].append({
            'name': states[s].stateName,
            'parent': states[s].stateParent,
            'entryFunctions': states[s].entryFunctions,
            'exitFunctions': states[s].exitFunctions,
            'transitions': states[s].transitions,
            'initialTransition': states[s].initialTransition,
            'junction': states[s].junction
        })
    jsonDump['events'] = []
    for t in masterTransList:
        jsonDump['events'].append(t)
        
    jsonDump['files'] = {}
    for f in files:
        jsonDump['files'][f] = files[f]
        
    
        
    with open('JSON/qsmIn.txt', 'w') as outfile:
        json.dump(jsonDump, outfile)
    
if __name__ == "__main__":
  
    # calling main function
    main()
from collections import deque
from random import choice, randint

node_names = ["admiring",
              "adoring",
              "affectionate",
              "agitated",
              "amazing",
              "angry",
              "awesome",
              "backstabbing",
              "berserk",
              "big",
              "boring",
              "clever",
              "cocky",
              "compassionate",
              "condescending",
              "cranky",
              "desperate",
              "determined",
              "distracted",
              "dreamy",
              "drunk",
              "eager",
              "ecstatic",
              "elastic",
              "elated",
              "elegant",
              "evil",
              "fervent",
              "focused",
              "furious",
              "gigantic",
              "gloomy",
              "goofy",
              "grave",
              "happy",
              "high",
              "hopeful",
              "hungry",
              "infallible",
              "jolly",
              "jovial",
              "kickass",
              "lonely",
              "loving",
              "mad",
              "modest",
              "naughty",
              "nauseous",
              "nostalgic",
              "peaceful",
              "pedantic",
              "pensive",
              "prickly",
              "reverent",
              "romantic",
              "sad",
              "serene",
              "sharp",
              "sick",
              "silly",
              "sleepy",
              "small",
              "stoic",
              "stupefied",
              "suspicious",
              "tender",
              "thirsty",
              "tiny",
              "trusting",
              "zen"]

def node(nid):
    name = choice(node_names) + "-" + str(randint(1000,9999))
    return {"name": name, "id": nid, "adj": set()}


def generate_graph(nodes):
    graph = []
    for n in range(0, nodes):
        n = node(n)
        for i in range(randint(0, 5)):
            n['adj'].add(randint(0, nodes-1))
        graph.append(n)
    return graph

g = generate_graph(50)


def bfs(graph, root_n):
    k = []
    for i in range(0, len(graph)):
        k.append({"distance": None, "parent": None})

    root = graph[root_n]
    Q = deque()
    k[root_n]['distance'] = 0
    Q.append(root)

    while len(Q) > 0:
        current = Q.pop()
        for adjecent_node_n in current['adj']:
            if not k[adjecent_node_n]['distance']:
                k[adjecent_node_n]['distance'] = k[current['id']]['distance'] + 1
                k[adjecent_node_n]['parent'] = current['id']
                Q.append(graph[adjecent_node_n])
    return k


def print_distances(graph, tree):
    for n, i in enumerate(tree):
        name = graph[n]['name']
        print(n, name, "with distance of", i['distance'], "from root, its parent is", i['parent'])


if __name__=="__main__":
    # start
    print_distances(g, bfs(g, 0))
    pass

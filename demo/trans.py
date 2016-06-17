import jinja2
import json
import sys


def main():
    script = []
    # fname = sys.argv[1]
    fname = '../src/bacteria simulation/bacteria simulation/log.txt'
    f = open(fname, 'r')
    for l in f.readlines():
        t = l.split()
        d = {}
        for i in xrange(len(t) / 5):
            d[t[i*5]] = {
                'x': float(t[i*5+1]),
                'y': float(t[i*5+2]),
                'r': float(t[i*5+3]),
                'e': float(t[i*5+4]),
            }
            if int(t[i*5]) < 0:
                print t[i*5]
        script.append(d)

    env = jinja2.Environment(loader=jinja2.FileSystemLoader('.'))
    template = env.get_template('index.html')
    fi = template.render(script=json.dumps(script))
    # of = open(fname+'.html', 'w')
    of = open('log.html', 'w')
    of.write(fi)


main()

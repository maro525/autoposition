
#include <iostream.h>
#include <sockinet.h>
#include <std.h>
#include <LEDA/graph.h>
#include <LEDA/queue.h>
#include <LEDA/string.h>
#include "parser.h"
#include "GraphManager.h"
main(int argc, char **argv)
{
    int portno;
    char buf[1024];
    string str, nm;
    sockinetbuf si(sockbuf::sock_stream);
    portno = atoi(argv[1]);
    si.bind(si.localhost(), portno);
    si.listen();
    queue<string> ReceiveQueue, SendQueue;
    MessageParser mp, *p;
    GraphManager GM(&mp);
    while (1)
    {
        iosockinet s = si.accept();
        while (!(ReceiveQueue.empty()))
            ReceiveQueue.pop();
        52 while (s >> buf)
        {
            ReceiveQueue.append(buf);
            cout << buf << endl;
            str = buf;
            if (str(0, 5) == "Layout")
            {
                mp.parse(&ReceiveQueue, &GM);
                if (str != "Layout:TellMeAlgorithms")
                {
                }
                else
                {
                }
            }
        }
    }
    GM.SendAlgorithms(s);
    break;
    GM.SendResult(s);
    si.close();
    cout << endl;
}
GraphManager.C
#include <LEDA/list.h>
#include <LEDA/point.h>
#include <LEDA/graph.h>
#include <std.h>
#include "GraphManager.h"
#include "parser.h"
#include "Node.h"
#include "Layouter.h"
    void
    GraphManager::GenerateGraph(list<string> *l1, list<string> *l2)
{
    int i, w, h, type;
    double x, y;
    string s, id;
    list<int> ilist;
    node n;
    Node N;
    if (l1->empty() != 1)
    {
        id = l1->pop();
        type = atoi(l1->pop());
        x = atoi(l1->pop());
        y = atoi(l1->pop());
        w = atoi(l1->pop());
        h = atoi(l1->pop());
        53

            x = x + w / 2;
        y = y + h / 2;
        Graph[Graph.new_node()] = Node(id, type, x, y, w, h);
        N = Graph[Graph.last_node()];
    }
    if (l2->empty() != 1)
    {
        string sn, en;
        list<point> l;
        id = l2->pop();
        type = atoi(l2->pop());
        sn = l2->pop();
        en = l2->pop();
        int i, lgt;
        node n1, n2;
        lgt = l2->length();
        for (i = 0; i < lgt; i = i + 2)
        {
            x = atoi(l2->pop());
            y = atoi(l2->pop());
            l.append(point(x, y));
        }
        forall_nodes(n, Graph)
        {
            s = Graph[n].GetNodeId();
            if (sn == s)
                n1 = n;
            if (en == s)
                n2 = n;
        }
        Graph[Graph.new_edge(n1, n2)] = Edge(id, type, l);
        //DisplayGraphState();
    }
}
void GraphManager::DisplayGraphState()
{
    node n;
    edge e;
    Node N;
    Edge E;
    cout << "*******" << endl;
    cout << "NodeNum: " << Graph.number_of_nodes() << endl;
    forall_nodes(n, Graph)
    {
        N = Graph[n];
        cout << "=============" << endl;
        cout << "NodeId: " << N.GetNodeId() << endl;
        cout << "NodeType: " << N.GetNodeType() << endl;
        54

            cout
            << "X: " << N.xcoord() << endl;
        cout << "Y: " << N.ycoord() << endl;
        cout << "W: " << N.GetWidth() << endl;
        cout << "H: " << N.GetHeight() << endl;
    }
    cout << "*******" << endl;
    cout << "EdgeNum: " << Graph.number_of_edges() << endl;
    forall_edges(e, Graph)
    {
        E = Graph[e];
        cout << "********** " << endl;
        cout << "EdgeId: " << E.GetEdgeId() << endl;
        N = Graph[Graph.source(e)];
        cout << "StartNode: " << N.GetNodeId() << endl;
        N = Graph[Graph.target(e)];
        cout << "EndNode: " << N.GetNodeId() << endl;
        cout << "EdgeType: " << E.GetEdgeType() << endl;
        cout << "EdgeLine: " << E.GetEdgeLine() << endl;
    }
}
void GraphManager::SendResult(iosockinet s)
{
    node n;
    Node N;
    string str;
    int x, y, w, h;
    s << "Graph" << endl;
    str = "node:";
    forall_nodes(n, Graph)
    {
        N = Graph[n];
        x = (int)(N.xcoord() - N.GetWidth() / 2);
        y = (int)(N.ycoord() - N.GetHeight() / 2);
        w = (int)N.GetWidth();
        h = (int)N.GetHeight();
        s << str << N.GetNodeId() << "," << N.GetNodeType() << ","
          << x << "," << y << "," << w
    }
    << "," << h << endl;
    str = "edge:";
    int i, l;
    edge e;
    Edge E;
    Node N1, N2;
    point p;
    55

        list<point>
            lt;
    forall_edges(e, Graph)
    {
        E = Graph[e];
        N1 = Graph[Graph.source(e)];
        N2 = Graph[Graph.target(e)];
        s << str << E.GetEdgeId() << "," << E.GetEdgeType() << ","
          << N1.GetNodeId() << "," << N2.GetNodeId();
        lt = E.GetEdgeLine();
        l = lt.length();
        for (i = 0; i < l; i++)
        {
            p = lt.pop();
            s << "," << (int)p.xcoord() << "," << (int)p.ycoord();
        }
        s << endl;
    }
    s << "Layout" << endl;
}
void GraphManager::GraphLayout(string algm)
{
    Layouter *layouter;
    if (algm == "Layout:Spring,StraightLine")
    {
        layouter = new Layouter(new SpringNodePlacer, new StraightLine, &Graph);
    }
    if (algm == "Layout:MagneticSpring,StraightLine")
    {
        layouter = new Layouter(new MagneticNodePlacer, new StraightLine, &Graph);
    }
    if (algm == "Layout:MNLmentalmap,StraightLine")
    {
        layouter = new Layouter(new MNLmentalmap, new StraightLine, &Graph);
    }
    return;
}
layouter->layout();
delete layouter;
}
NodePlacer.C
#include "NodePlacer.h"
#include <math.h>
#include <LEDA/string.h>
#include <LEDA/polygon.h>
    56

#include <LEDA/list.h>
#include <LEDA/node_matrix.h>
#include <LEDA/node_set.h>
#include "TreeLayouter.h"
#define ITERATION 100
#define NODEMAX 100
#define EDGEMAX 100
#define DC1 20.0
#define DC2 70.0
#define DC3 100.0
#define DC4 0.2
#define CanvasMinx 150
#define CanvasMiny 150
#define Space 20
    node
    get_node_fromid(GRAPH<Node, Edge> &g, string id);
double NodePlacer::CheckOverlap(GRAPH<Node, Edge> &Graph,
                                node v, node w)
{
    double vx1, vy1, vx2, vy2, wx1, wy1, wx2, wy2, dx, dy, l;
    list<point> pl1, pl2;
    vx1 = Graph[v].xcoord() - Graph[v].GetWidth() / 2 - Space;
    vy1 = Graph[v].ycoord() - Graph[v].GetHeight() / 2 - Space;
    vx2 = Graph[v].xcoord() + Graph[v].GetWidth() / 2 + Space;
    vy2 = Graph[v].ycoord() + Graph[v].GetHeight() / 2 + Space;
    pl1.append(point(vx1, vy1));
    pl1.append(point(vx2, vy1));
    pl1.append(point(vx2, vy2));
    pl1.append(point(vx1, vy2));
    polygon pg(pl1);
    wx1 = Graph[w].xcoord() - Graph[w].GetWidth() / 2 - Space;
    wy1 = Graph[w].ycoord() - Graph[w].GetHeight() / 2 - Space;
    wx2 = Graph[w].xcoord() + Graph[w].GetWidth() / 2 + Space;
    wy2 = Graph[w].ycoord() + Graph[w].GetHeight() / 2 + Space;
    pl2.append(point(wx1, wy1));
    pl2.append(point(wx2, wy1));
    pl2.append(point(wx2, wy2));
    pl2.append(point(wx1, wy2));
    polygon pg2(pl2);
    double r = 0, olp1, olp2, olp3, olp4;
    point t, *co;
    57

        if (pg.inside(point(wx1, wy1)) == 1)
    {
        t = point(vx2, vy2);
        r = Graph[v].distance(t);
        return r;
    }
    if (pg.inside(point(wx2, wy1)) == 1)
    {
        t = point(vx1, vy2);
        r = Graph[v].distance(t);
        return r;
    }
    if (pg.inside(point(wx2, wy2)) == 1)
    {
        t = point(vx1, vy1);
        r = Graph[v].distance(t);
        return r;
    }
    if (pg.inside(point(wx1, wy2)) == 1)
    {
        t = point(vx2, vy1);
        r = Graph[v].distance(t);
        return r;
    }
    if (pg2.inside(point(vx1, vy1)) == 1)
    {
        t = point(wx2, wy2);
        r = Graph[w].distance(t);
        return r;
    }
    if (pg2.inside(point(vx2, vy1)) == 1)
    {
        t = point(wx1, wy2);
        r = Graph[w].distance(t);
        return r;
    }
    if (pg2.inside(point(vx2, vy2)) == 1)
    {
        t = point(wx1, wy1);
        r = Graph[w].distance(t);
        return r;
    }
    if (pg2.inside(point(vx1, vy2)) == 1)
    {
        t = point(wx2, wy1);
        r = Graph[w].distance(t);
        return r;
    }
    if (r != 0)
    {
        return r;
    }
    return 0;
}
void NodePlacer::ShiftGraph(GRAPH<Node, Edge> &Graph)
{
    double minx, miny;
    58

        node n1;
    minx = Graph[Graph.first_node()].xcoord() - Graph[Graph.first_node()].GetWidth() / 2;
    miny = Graph[Graph.first_node()].ycoord() - Graph[Graph.first_node()].GetWidth() / 2;
    forall_nodes(n1, Graph)
    {
        if (minx > Graph[n1].xcoord() - Graph[n1].GetWidth() / 2)
            minx = Graph[n1].xcoord() - Graph[n1].GetWidth() / 2;
        if (miny > Graph[n1].ycoord() - Graph[n1].GetHeight() / 2)
            miny = Graph[n1].ycoord() - Graph[n1].GetHeight() / 2;
    }
    double x, y;
    if (minx != CanvasMinx || miny != CanvasMiny)
    {
        forall_nodes(n1, Graph)
        {
            x = Graph[n1].xcoord();
            y = Graph[n1].ycoord();
    Graph[n1] = Node(Graph[n1].GetNodeId(), Graph[n1].GetNodeType(),
    x-(minx - CanvasMinx), y-(miny - CanvasMiny),
        }
    }
}
Graph[n1].GetWidth(), Graph[n1].GetHeight());
point NodePlacer::GetCorner(GRAPH<Node, Edge> &Graph, int p)
{
    double minx, miny, maxx, maxy;
    node n;
    minx = Graph[Graph.first_node()].xcoord();
    miny = Graph[Graph.first_node()].ycoord();
    maxx = minx;
    maxy = miny;
    forall_nodes(n, Graph)
    {
        if (minx > Graph[n].xcoord())
            minx = Graph[n].xcoord();
        if (miny > Graph[n].ycoord())
            miny = Graph[n].ycoord();
        if (maxx < Graph[n].xcoord())
            maxx = Graph[n].xcoord();
        if (maxy < Graph[n].ycoord())
            maxy = Graph[n].ycoord();
    }
    switch (p)
    {
    case 0:
        return point(minx, miny);
    case 1:
        return point(maxx, miny);
    case 2:
        return point(maxx, maxy);
    case 3:
        return point(minx, maxy);
    }
}
int NodePlacer::EliminateOverlap(GRAPH<Node, Edge> &Graph, int TreeMove)
{
    node nd, n1, n2;
    edge e;
    int N = 0;
    59

        point p1,
        p2;
    double x, y, ovr, l, deltaX, deltaY, d1, d2, S, W = 1000, H = 1000;
    list<node> NodeList, OverlapList;
    node_set NS(Graph);
    forall_nodes(nd, Graph)
    {
        forall_inout_edges(e, nd)
        {
            if (Graph[e].GetEdgeType() == 3 && TreeMove == 0)
            {
                NS.insert(nd);
            }
        }
    }
    TreeLayouter *TL;
    forall_nodes(nd, Graph)
    {
        NodeList.append(nd);
        if ((l = Graph[nd].GetWidth()) < W)
            W = l;
        if ((l = Graph[nd].GetHeight()) < H)
            H = l;
    }
    NodeList.pop();
    W = W / 2;
    H = H / 2;
    p1 = GetCorner(Graph, 0);
    p2 = GetCorner(Graph, 2);
    x = (p1.xcoord() + p2.xcoord()) / 2;
    y = (p1.ycoord() + p2.ycoord()) / 2;
    point cm(x, y);
    forall_nodes(n1, Graph)
    {
        forall(n2, NodeList)
        {
            if ((ovr = CheckOverlap(Graph, n1, n2)) != 0)
            {
                if (Graph[n1].distance(cm) > Graph[n2].distance(cm))
                    nd = n1;
                else
                    nd = n2;
                S = Graph[nd].distance(cm);
                d1 = (Graph[nd].xcoord() - cm.xcoord()) / S;
                d2 = (Graph[nd].ycoord() - cm.ycoord()) / S;
                if (W < ovr)
                    deltaX = d1 * W;
                else
                    deltaX = d1 * ovr;
                if (H < ovr)
                    deltaY = d2 * H;
                else
                    deltaY = d2 * ovr;
                x = Graph[nd].xcoord();
                y = Graph[nd].ycoord();
                60

                    //   if(!(NS.member(nd))){
                    // if(nd == n1)nd = n2; else nd = n1;
                    Graph[nd] = Node(Graph[nd].GetNodeId(), Graph[nd].GetNodeType(),
                                     x + deltaX, y + deltaY, Graph[nd].GetWidth(), Graph[nd].GetHeight());
                OverlapList.append(nd);
                // }
            }
        }
        if (NodeList.empty() != -1)
        {
            NodeList.pop();
        }
        else
            break;
    }
    NodeList.clear();
    forall_nodes(nd, Graph)
    {
        NodeList.append(nd);
    }
    NodeList.pop();
    forall(n1, OverlapList)
    {
        forall_nodes(n2, Graph)
        {
            if (n1 != n2)
            {
                if ((ovr = CheckOverlap(Graph, n1, n2)) != 0)
                    N++;
            }
        }
    }
    return N;
}
node get_node_fromid(GRAPH<Node, Edge> &g, string id)
{
    node n;
    forall_nodes(n, g)
    {
        if (id == g[n].GetNodeId())
            return n;
    }
    return nil;
}
MNLayouter.C
#include "NodePlacer.h"
#include <math.h>
#include <LEDA/node_matrix.h>
#define ITERATION 1000
#define PI M_PI  //π
#define DC1 30.0 //スプリング定数
    61

#define DC2 100.0
#define DC3 20000.0
#define DC4 0.05
#define DC5 0.01
#define DC6 0.01
#define DC7 0.01
#define DC8 10.0
#define DC9 1
#define DC10
#define DC11
#define DC12
#define DC13
#define DC14
    // スプリングの長さ
    // 非隣接頂点間定数 (使ってない) // 微小移動量定数
    // 関連エッジの磁力定数
    // 集約エッジの磁力定数
    // 継承エッジの磁力定数
    // 磁場の強さ
    // 辺の長さの回転力への影響
    // 角度の回転力への影響
    // 関連エッジの角度
    // 集約エッジの角度
    // 継承エッジの角度 //InertailForce 係数
    1 0 PI /
    4.0 PI / 2.0 0.1 extern node get_node_fromid(GRAPH<Node, Edge> &g, string id);
void MagneticNodePlacer2::NodeLayout(GRAPH<Node, Edge> &Graph)
{
    node n1, n2, n3;
    edge e;
    int i;
    double x, y, w, h, d1, d2;
    double nx = 0, ny = 0;
    node_array<double> forcex(Graph), forcey(Graph);
    node_array<double> C4(Graph);
    node_array<double> C5(Graph);
    node_array<double> CX(Graph);
    node_array<double> CY(Graph);
    node_matrix<double> C1(Graph);
    node_matrix<double> C2(Graph);
    node_matrix<double> C3(Graph);
    // 定数の決定 forall_nodes(n1,Graph){
    forall_nodes(n2, Graph)
    {
        d1 = sqrt(pow((Graph[n1].GetWidth() / 2), 2) + pow((Graph[n1].GetHeight() / 2), 2));
        d2 = sqrt(pow((Graph[n2].GetWidth() / 2), 2) + pow((Graph[n2].GetHeight() / 2), 2));
        // スプリング定数 C1(n1,n2) = DC1;
        // スプリングの自然長 C2(n1,n2) = DC2;
        // 非隣接頂点間定数
        C3(n1, n2) = DC3;
    }
    // 微小移動量定数
    62

        C4[n1] = DC4;
    C5[n1] = DC14;
    CX[n1] = Graph[n1].xcoord();
    CY[n1] = Graph[n1].ycoord();
}
for (i = 0; i < ITERATION; i++)
{
    forall_nodes(n1, Graph)
    {
        forcex[n1] = 0;
        forcey[n1] = 0;
        forall_nodes(n2, Graph)
        {
            int flag = 0;
            if (n1 != n2)
            {
                forall_inout_edges(e, n1)
                {
                    if (Graph.opposite(n1, e) == n2 && Graph.opposite(n2, e) == n1)
                    {
                        //n1 と n2 が辺 e で隣接していた時スプリングによる力を計算
                        forcex[n1] = forcex[n1] + AttractiveForce(Graph, n1, n2, 0, C1[n1][n2], C2[n1][n2]);
                        forcey[n1] = forcey[n1] + AttractiveForce(Graph, n1, n2, 1, C1[n1][n2], C2[n1][n2]);
                        //n1 と n2 が関連関係の時磁力を計算
                        if (Graph[e].GetEdgeType() == 1)
                        {
                            forcex[n1] = forcex[n1] + MagneticForce(Graph, n1, n2, 0, 1, DC5, DC8, DC9, DC10, DC11);
                            forcey[n1] = forcey[n1] + MagneticForce(Graph, n1, n2, 0, 2, DC5, DC8, DC9, DC10, DC11);
                        }
                        //n1 が集約関係の親の時磁力を計算
                        if (Graph[e].GetEdgeType() == 2 && n1 == Graph.source(e))
                        {
                            forcex[n1] = forcex[n1] + MagneticForce(Graph, n1, n2, 1, 1, DC6, DC8, DC9, DC10, DC12);
                            forcey[n1] = forcey[n1] + MagneticForce(Graph, n1, n2, 1, 2, DC6, DC8, DC9, DC10, DC12);
                        }
                        //n1 が集約関係の子の時磁力を計算
                        if (Graph[e].GetEdgeType() == 2 && n1 == Graph.target(e))
                        {
                            forcex[n1] = forcex[n1] + MagneticForce(Graph, n1, n2, 2, 1, DC6, DC8, DC9, DC10, DC12);
                            forcey[n1] = forcey[n1] + MagneticForce(Graph, n1, n2, 2, 2, DC6, DC8, DC9, DC10, DC12);
                        }
                        //n1 が継承関係の親の時磁力を計算
                        if (Graph[e].GetEdgeType() == 3 && n1 == Graph.source(e))
                        {
                            forcex[n1] = forcex[n1] + MagneticForce(Graph, n1, n2, 1, 1, DC7, DC8, DC9, DC10, DC13);
                            forcey[n1] = forcey[n1] + MagneticForce(Graph, n1, n2, 1, 2, DC7, DC8, DC9, DC10, DC13);
                        }
                        //n1 が継承関係の子の時磁力を計算
                        if (Graph[e].GetEdgeType() == 3 && n1 == Graph.target(e))
                        {
                            forcex[n1] = forcex[n1] + MagneticForce(Graph, n1, n2, 2, 1, DC7, DC8, DC9, DC10, DC13);
                            forcey[n1] = forcey[n1] + MagneticForce(Graph, n1, n2, 2, 2, DC7, DC8, DC9, DC10, DC13);
                        }
                        63

                            flag = 1;
                    }
                }
                // 隣接していない時斥力を計算 if (flag == 0){
                forcex[n1] = forcex[n1] + RepulsiveForce(Graph, n1, n2, 0, C3[n1][n2]);
                forcey[n1] = forcey[n1] + RepulsiveForce(Graph, n1, n2, 1, C3[n1][n2]);
            }
        }
    }
}
// ノード n1 を移動する forall_nodes(n1,Graph){
x = Graph[n1].xcoord();
y = Graph[n1].ycoord();
x = x + C4[n1] * forcex[n1];
y = y + C4[n1] * forcey[n1];
Graph[n1] = Node(Graph[n1].GetNodeId(), Graph[n1].GetNodeType(),
                 x, y, Graph[n1].GetWidth(), Graph[n1].GetHeight());
}
}
cout << "┌─── 調整前の座標と大きさ ───┐ " << endl;
forall_nodes(n1, Graph)
{
    cout << Graph[n1].GetNodeId()
         << ":(" << Graph[n1].xcoord() - Graph[n1].GetWidth() / 2 << ","
         << Graph[n1].ycoord() - Graph[n1].GetHeight() / 2 << ")"
         << ":(" << Graph[n1].GetWidth() << ","
         << Graph[n1].GetHeight() << ")" << endl;
}
cout << "└─────────────────┘ " << endl; // 全体の位置の調整
ShiftGraph(Graph);
cout << "┌─── 調整後の座標と大きさ ───┐ " << endl;
forall_nodes(n1, Graph)
{
    cout << Graph[n1].GetNodeId()
         << ":(" << Graph[n1].xcoord() - Graph[n1].GetWidth() / 2 << ","
         << Graph[n1].ycoord() - Graph[n1].GetHeight() / 2 << ")"
         << ":(" << Graph[n1].GetWidth() << ","
         << Graph[n1].GetHeight() << ")" << endl;
}
cout << "└─────────────────┘ " << endl;
cout << "magneticspring-end" << endl;
}
64

    double
    MagneticNodePlacer2::AttractiveForce(GRAPH<Node, Edge> &Graph,
                                         node v, node w, int axis, double c, double d0)
{
    double d, dc, f, dx, dy;
    dx = Graph[v].xcoord() - Graph[w].xcoord();
    dy = Graph[v].ycoord() - Graph[w].ycoord();
    d = GetDistance(Graph, v, w);
    dc = d / d0;
    f = -c * log(dc);
    if (f > 500)
        f = 500;
    if (f < -500)
        f = -500;
    switch (axis)
    {
    case 0:
        return f * (dx / d);
    case 1:
        return f * (dy / d);
    }
}
double MagneticNodePlacer2::RepulsiveForce(GRAPH<Node, Edge> &Graph,
                                           node v, node w, int axis, double c)
{
    double d, dc, f, fx, fy, dx, dy;
    dx = Graph[v].xcoord() - Graph[w].xcoord();
    dy = Graph[v].ycoord() - Graph[w].ycoord();
    d = GetDistance(Graph, v, w);
    f = c / (d * d);
    if (f > 500)
        f = 500;
    if (f < -500)
        f = -500;
    switch (axis)
    {
    case 0:
        return f * (dx / d);
    case 1:
        return f * (dy / d);
    }
}
int intersect2(GRAPH<Node, Edge> &Graph, node v, node w)
{
  if ((Graph[v].xcoord()-Graph[v].GetWidth()/2) <
65

             (Graph[w].xcoord()+Graph[w].GetWidth()/2)&&
(Graph[w].xcoord()-Graph[w].GetWidth()/2) <
             (Graph[v].xcoord()+Graph[v].GetWidth()/2)&&
(Graph[v].ycoord()-Graph[v].GetHeight()/2)<
             (Graph[w].ycoord()+Graph[w].GetHeight()/2)&&
(Graph[w].ycoord()-Graph[w].GetHeight()/2)<
    return 1;
  else
return 0;
}
(Graph[v].ycoord()+Graph[v].GetHeight()/2))
double MagneticNodePlacer2::GetDistance(GRAPH<Node,Edge>& Graph, node v, node w)
{
    double dLv, dRv, dLw, dRw, a, x1, x2, y1, y2;
    double vx, vy, wx, wy;
    // 重なっていた場合
    if (intersect2(Graph, v, w))
    {
        return 10;
    }
    // ノードに重なりがなかった場合 else{
    x1 = Graph[v].xcoord();
    y1 = Graph[v].ycoord();
    x2 = Graph[w].xcoord();
    y2 = Graph[w].ycoord();
    // 二つのノードが縦に並んでいた時 if (x1 == x2)
    if (y1 > y2)
    {
        return (Graph[v].ycoord() - Graph[v].GetHeight() / 2) -
               (Graph[w].ycoord() + Graph[w].GetHeight() / 2);
    }
    else
    {
        return (Graph[w].ycoord() - Graph[w].GetHeight() / 2) -
               (Graph[v].ycoord() + Graph[v].GetHeight() / 2);
    }
    // 二つのノードが横に並んでいた時 if (y1 == y2)
    if (x1 > x2)
    {
        return (Graph[v].xcoord() - Graph[v].GetWidth() / 2) -
               (Graph[w].xcoord() + Graph[w].GetWidth() / 2);
    }
    else
    {
        return (Graph[w].xcoord() - Graph[w].GetWidth() / 2) -
               (Graph[v].xcoord() + Graph[v].GetWidth() / 2); // ノードが重なってもいなく真横、真縦にも並んでいない場合
    }
    66

        a = (y1 - y2) / (x1 - x2);
    dRv = -Graph[v].GetHeight() / Graph[v].GetWidth();
    dLv = Graph[v].GetHeight() / Graph[v].GetWidth();
    dRw = -Graph[w].GetHeight() / Graph[w].GetWidth();
    dLw = Graph[w].GetHeight() / Graph[w].GetWidth();
    //cout << "dRv:" << dRv << ", dLv:" << dLv << " ,a:" <<a << endl;
    //v は第1象現の上
    if (x1 < x2 && y1 > y2 && dRv > a)
    {
        vy = Graph[v].ycoord() - Graph[v].GetHeight() / 2;
        vx = (vy - y1 + a * x1) / a;
        //w は第3象現の上
        if (dRw < a)
        {
            wx = Graph[w].xcoord() - Graph[w].GetWidth() / 2;
            wy = a * wx + y1 - a * x1;
        }
        //w は第3象現の下 else{
        wy = Graph[w].ycoord() + Graph[w].GetHeight() / 2;
        wx = (wy - y1 + a * x1) / a;
    }
}
//v は第1象現の下
else if (x1 < x2 && y1 > y2 && dRv < a)
{
    vx = Graph[v].xcoord() + Graph[v].GetWidth() / 2;
    vy = a * vx + y1 - a * x1;
    //w は第3象現の上
    if (dRw < a)
    {
        wx = Graph[w].xcoord() - Graph[w].GetWidth() / 2;
        wy = a * wx + y1 - a * x1;
    }
    //w は第3象現の下 else{
    wy = Graph[w].ycoord() + Graph[w].GetHeight() / 2;
    wx = (wy - y1 + a * x1) / a;
}
}
//v は第2象現の上
else if (x1 < x2 && y2 > y1 && dLv > a)
{
    vx = Graph[v].xcoord() + Graph[v].GetWidth() / 2;
    vy = a * vx + y1 - a * x1;
    //w は第4象現の下
    if (dLw > a)
    {
        wx = Graph[w].xcoord() - Graph[w].GetWidth() / 2;
        wy = a * wx + y1 - a * x1;
    }
    //w は第4象現の上 else{
    67

        wy = Graph[w].ycoord() - Graph[w].GetHeight() / 2;
    wx = (wy - y1 + a * x1) / a;
}
}
//v は第2象現の下
else if (x1 < x2 && y2 > y1 && dLv < a)
{
    vy = Graph[v].ycoord() + Graph[v].GetHeight() / 2;
    vx = (vy - y1 + a * x1) / a;
    //w は第4象現の下
    if (dLw > a)
    {
        wx = Graph[w].xcoord() - Graph[w].GetWidth() / 2;
        wy = a * wx + y1 - a * x1;
    }
    //w は第4象現の上 else{
    wy = Graph[w].ycoord() - Graph[w].GetHeight() / 2;
    wx = (wy - y1 + a * x1) / a;
}
}
//v は第3象現の下
else if (x2 < x1 && y2 > y1 && dRv > a)
{
    vy = Graph[v].ycoord() + Graph[v].GetHeight() / 2;
    vx = (vy - y1 + a * x1) / a;
    //w は第1象現の上
    if (dRw > a)
    {
        wy = Graph[w].ycoord() - Graph[w].GetHeight() / 2;
        wx = (wy - y1 + a * x1) / a;
    }
    //w は第1象現の下 else{
    wx = Graph[w].xcoord() + Graph[w].GetWidth() / 2;
    wy = a * wx + y1 - a * x1;
}
}
//v は第3象現の上
else if (x2 < x1 && y2 > y1 && dRv < a)
{
    vx = Graph[v].xcoord() - Graph[v].GetWidth() / 2;
    vy = a * vx + y1 - a * x1;
    //w は第1象現の上
    if (dRw > a)
    {
        wy = Graph[w].ycoord() - Graph[w].GetHeight() / 2;
        wx = (wy - y1 + a * x1) / a;
    }
    //w は第1象現の下 else{
    wx = Graph[w].xcoord() + Graph[w].GetWidth() / 2;
    wy = a * wx + y1 - a * x1;
}
}
//v は第4象現の下
68

    else if (x2 < x1 && y1 > y2 && dLv > a)
{
    vx = Graph[v].xcoord() - Graph[v].GetWidth() / 2;
    vy = a * vx + y1 - a * x1;
    //w は第2象現の上
    if (dLw > a)
    {
        wx = Graph[w].xcoord() + Graph[w].GetWidth() / 2;
        wy = a * wx + y1 - a * x1;
    }
    //w は第2象現の下 else{
    wy = Graph[w].ycoord() + Graph[w].GetHeight() / 2;
    wx = (wy - y1 + a * x1) / a;
}
}
//v は第4象現の上
else if (x2 < x1 && y1 > y2 && dLv < a)
{
    vy = Graph[v].ycoord() - Graph[v].GetHeight() / 2;
    vx = (vy - y1 + a * x1) / a;
    //w は第2象現の上
    if (dLw > a)
    {
        wx = Graph[w].xcoord() + Graph[w].GetWidth() / 2;
        wy = a * wx + y1 - a * x1;
    }
    //w は第2象現の下 else{
    wy = Graph[w].ycoord() + Graph[w].GetHeight() / 2;
    wx = (wy - y1 + a * x1) / a;
}
}
return sqrt((pow((vx - wx), 2)) + (pow((vy - wy), 2)));
}
}
double MagneticNodePlacer2::MagneticForce(GRAPH<Node, Edge> &Graph,
                                          node v, node w, int axisST, int axisXY, double c,
                                          double b, int alpha, int beta, double K)
{
    double d, dx, dy, dk, t, f, k;
    d = Graph[v].distance(Graph[w]);
    dx = (Graph[v].xcoord() - Graph[w].xcoord());
    dy = (Graph[v].ycoord() - Graph[w].ycoord());
    dk = atan2(dy, dx);
    //source のノードについて求める時は磁界の向きを逆転させる if (axisST == 1){
    if (K > 0)
        k = K - PI;
    else
        k = PI + K;
}
69

    //target の時はそのまま else if (axisST == 2)
    k = K;
// 無向磁針の時は角度の小さい方を磁界の向きにする else if (axisST ==0){
if (fabs(K - dk) > 3.0 / 2.0 * PI || PI / 2.0 >= fabs(K - dk))
    k = K;
else if (3.0 / 2.0 * PI >= fabs(K - dk) || fabs(K - dk) > PI / 2.0)
    if (K > 0)
        k = K - PI;
    else
        k = PI + K;
}
// 磁界と自分のなす角を求める if (fabs(k - dk) > PI)
t = fabs(k - dk - 2.0 * PI);
else t = fabs(k - dk);
// なす角が 0, または距離が 0 の時は磁力も 0 if (d == 0 ||t == 0)
return 0;
f = c * b * pow(d, alpha) * pow(t, beta);
if (k < 0)
{
    if ((dx < 0 && dy < 0) || (dx >= 0 && dy >= 0))
    {
        if (k < -PI / 2.0 && ((PI / 2.0 >= dk && dk > PI + k) || (k < dk && dk < -PI / 2.0)))
        {
            if (axisXY == 1)
            {
                return -f * (fabs(dy) / d);
            }
            else
            {
                return f * (fabs(dx) / d);
            }
        }
        else
        {
            if (axisXY == 1)
            {
                return f * (fabs(dy) / d);
            }
            else
            {
                return -f * (fabs(dx) / d);
            }
        }
    }
    else if ((dx < 0 && dy >= 0) || (dx >= 0 && dy < 0))
    {
        if (k > -PI / 2.0 && ((-PI / 2.0 < dk && dk < k) || (PI / 2.0 < dk && dk < PI + k)))
        {
            if (axisXY == 1)
            {
                return f * (fabs(dy) / d);
                70
            }
            else
            {
                return f * (fabs(dx) / d);
            }
        }
        else
        {
            if (axisXY == 1)
            {
                return -f * (fabs(dy) / d);
            }
            else
            {
                return -f * (fabs(dx) / d);
            }
        }
    }
}
if (k >= 0)
{
    if ((dx < 0 && dy < 0) || (dx >= 0 && dy >= 0))
    {
        if (k < PI / 2.0 && ((PI / 2.0 > dk && dk > k) || (k - PI < dk && dk < -PI / 2.0)))
        {
            if (axisXY == 1)
            {
                return f * (fabs(dy) / d);
            }
            else
            {
                return -f * (fabs(dx) / d);
            }
        }
        else
        {
            if (axisXY == 1)
            {
                return -f * (fabs(dy) / d);
            }
            else
            {
                return f * (fabs(dx) / d);
            }
        }
    }
    else if ((dx < 0 && dy >= 0) || (dx >= 0 && dy < 0))
    {
        if (k > PI / 2.0 && ((-PI / 2.0 < dk && dk < k - PI) || (PI / 2.0 < dk && dk < k)))
        {
            if (axisXY == 1)
            {
                return -f * (fabs(dy) / d);
            }
            else
            {
                return -f * (fabs(dx) / d);
            }
        }
        else
        {
            if (axisXY == 1)
            {
                return f * (fabs(dy) / d);
            }
            else
            {
                return f * (fabs(dx) / d);
                71
            }
        }
    }
}
}
// ノードを円周上に初期配置する
int MagneticNodePlacer2::init(GRAPH<Node, Edge> &Graph)
{
    int NodeNum;
    int ox = 300, oy = 300, r;
    double angle, da;
    node nd;
    node_array<double> xp(Graph), yp(Graph);
    NodeNum = Graph.number_of_nodes(); //全ノード数 angle = 6.28 / NodeNum; //角度差
    r = NodeNum * 5 + 40;              //半径
    da = 0.0;                          //角度
    forall_nodes(nd, Graph)
    {
        xp[nd] = r * cos(da) + ox;
        yp[nd] = r * sin(da) + oy;
        Graph[nd] = Node(Graph[nd].GetNodeId(), Graph[nd].GetNodeType(),
                         xp[nd], yp[nd], Graph[nd].GetWidth(), Graph[nd].GetHeight());
        da += angle;
    }
}
MNLwithMentalmap.C
#include "NodePlacer.h"
#include <math.h>
#include <LEDA/node_matrix.h>
#define ITERATION 1000
#define PI M_PI
#define DC1 30.0
#define DC2 100.0
#define DC3 20000.0
#define DC4 0.05
#define DC5 0.01
#define DC6 0.01
#define DC7 0.01
#define DC8 10.0
#define DC9 1
#define DC10
#define DC11
#define DC12
    // π
    // スプリング定数
    // スプリングの長さ
    // 非隣接頂点間定数 (使ってない)
    // 微小移動量定数
    // 関連エッジの磁力定数 // 集約エッジの磁力定数 // 継承エッジの磁力定数
    // 磁場の強さ
    // 辺の長さの回転力への影響 // 角度の回転力への影響
    // 関連エッジの角度
    // 集約エッジの角度
    1 0 PI /
    4.0 72

#define DC13 PI / 2.0 // 継承エッジの角度 #define DC14 0.1 //InertailForce係数
    extern node
    get_node_fromid(GRAPH<Node, Edge> &g, string id);
void MNLmentalmap::NodeLayout(GRAPH<Node, Edge> &Graph)
{
    node n1, n2, n3;
    edge e;
    int i;
    double x, y, w, h, d1, d2;
    double nx = 0, ny = 0;
    node_array<double> forcex(Graph), forcey(Graph);
    //init(Graph);
    node_array<double> C4(Graph);
    node_array<double> C5(Graph);
    node_array<double> CX(Graph);
    node_array<double> CY(Graph);
    node_matrix<double> C1(Graph);
    node_matrix<double> C2(Graph);
    node_matrix<double> C3(Graph);
    // 定数の決定 forall_nodes(n1,Graph){
    forall_nodes(n2, Graph)
    {
        d1 = sqrt(pow((Graph[n1].GetWidth() / 2), 2) + pow((Graph[n1].GetHeight() / 2), 2));
        d2 = sqrt(pow((Graph[n2].GetWidth() / 2), 2) + pow((Graph[n2].GetHeight() / 2), 2));
        // スプリング定数 C1(n1,n2) = DC1;
        // スプリングの自然長 C2(n1,n2) = DC2;
        // 非隣接頂点間定数
        C3(n1, n2) = DC3;
    }
    // 微小移動量定数
    C4[n1] = DC4;
    C5[n1] = DC14;
    CX[n1] = Graph[n1].xcoord();
    CY[n1] = Graph[n1].ycoord();
}
for (i = 0; i < ITERATION; i++)
{
    forall_nodes(n1, Graph)
    {
        forcex[n1] = 0;
        73

            forcey[n1] = 0;
        forall_nodes(n2, Graph)
        {
            int flag = 0;
            if (n1 != n2)
            {
                forall_inout_edges(e, n1)
                {
                    if (Graph.opposite(n1, e) == n2 && Graph.opposite(n2, e) == n1)
                    {
                        //n1 と n2 が辺 e で隣接していた時スプリングによる力を計算
                        forcex[n1] = forcex[n1] + AttractiveForce(Graph, n1, n2, 0, C1[n1][n2], C2[n1][n2]);
                        forcey[n1] = forcey[n1] + AttractiveForce(Graph, n1, n2, 1, C1[n1][n2], C2[n1][n2]);
                        //n1 と n2 が関連関係の時磁力を計算
                        if (Graph[e].GetEdgeType() == 1)
                        {
                            forcex[n1] = forcex[n1] + MagneticForce(Graph, n1, n2, 0, 1, DC5, DC8, DC9, DC10, DC11);
                            forcey[n1] = forcey[n1] + MagneticForce(Graph, n1, n2, 0, 2, DC5, DC8, DC9, DC10, DC11);
                        }
                        //n1 が集約関係の親の時磁力を計算
                        if (Graph[e].GetEdgeType() == 2 && n1 == Graph.source(e))
                        {
                            forcex[n1] = forcex[n1] + MagneticForce(Graph, n1, n2, 1, 1, DC6, DC8, DC9, DC10, DC12);
                            forcey[n1] = forcey[n1] + MagneticForce(Graph, n1, n2, 1, 2, DC6, DC8, DC9, DC10, DC12);
                        }
                        //n1 が集約関係の子の時磁力を計算
                        if (Graph[e].GetEdgeType() == 2 && n1 == Graph.target(e))
                        {
                            forcex[n1] = forcex[n1] + MagneticForce(Graph, n1, n2, 2, 1, DC6, DC8, DC9, DC10, DC12);
                            forcey[n1] = forcey[n1] + MagneticForce(Graph, n1, n2, 2, 2, DC6, DC8, DC9, DC10, DC12);
                        }
                        //n1 が継承関係の親の時磁力を計算
                        if (Graph[e].GetEdgeType() == 3 && n1 == Graph.source(e))
                        {
                            forcex[n1] = forcex[n1] + MagneticForce(Graph, n1, n2, 1, 1, DC7, DC8, DC9, DC10, DC13);
                            forcey[n1] = forcey[n1] + MagneticForce(Graph, n1, n2, 1, 2, DC7, DC8, DC9, DC10, DC13);
                        }
                        //n1 が継承関係の子の時磁力を計算
                        if (Graph[e].GetEdgeType() == 3 && n1 == Graph.target(e))
                        {
                            forcex[n1] = forcex[n1] + MagneticForce(Graph, n1, n2, 2, 1, DC7, DC8, DC9, DC10, DC13);
                            forcey[n1] = forcey[n1] + MagneticForce(Graph, n1, n2, 2, 2, DC7, DC8, DC9, DC10, DC13);
                        }
                        flag = 1;
                    }
                }
                // 隣接していない時斥力を計算 if (flag == 0){
                forcex[n1] = forcex[n1] + RepulsiveForce(Graph, n1, n2, 0, C3[n1][n2]);
                forcey[n1] = forcey[n1] + RepulsiveForce(Graph, n1, n2, 1, C3[n1][n2]);
            }
            74
        }
    }
    forcex[n1] = forcex[n1] + InertialForce(Graph, n1, 0, C5[n1], CX[n1], CY[n1]);
    forcey[n1] = forcey[n1] + InertialForce(Graph, n1, 1, C5[n1], CX[n1], CY[n1]);
}
// ノード n1 を移動する forall_nodes(n1,Graph){
x = Graph[n1].xcoord();
y = Graph[n1].ycoord();
x = x + C4[n1] * forcex[n1];
y = y + C4[n1] * forcey[n1];
Graph[n1] = Node(Graph[n1].GetNodeId(), Graph[n1].GetNodeType(),
                 x, y, Graph[n1].GetWidth(), Graph[n1].GetHeight());
}
}
cout << "┌─── 調整前の座標と大きさ ───┐ " << endl;
forall_nodes(n1, Graph)
{
    cout << Graph[n1].GetNodeId()
         << ":(" << Graph[n1].xcoord() - Graph[n1].GetWidth() / 2 << ","
         << Graph[n1].ycoord() - Graph[n1].GetHeight() / 2 << ")"
         << ":(" << Graph[n1].GetWidth() << ","
         << Graph[n1].GetHeight() << ")" << endl;
}
cout << "└─────────────────┘ " << endl; // 全体の位置の調整
ShiftGraph(Graph);
cout << "┌─── 調整後の座標と大きさ ───┐ " << endl;
forall_nodes(n1, Graph)
{
    cout << Graph[n1].GetNodeId()
         << ":(" << Graph[n1].xcoord() - Graph[n1].GetWidth() / 2 << ","
         << Graph[n1].ycoord() - Graph[n1].GetHeight() / 2 << ")"
         << ":(" << Graph[n1].GetWidth() << ","
         << Graph[n1].GetHeight() << ")" << endl;
}
cout << "└─────────────────┘ " << endl;
cout << "magneticspring-end" << endl;
}
double MNLmentalmap::AttractiveForce(GRAPH<Node, Edge> &Graph,
                                     node v, node w, int axis, double c, double d0)
{
    double d, dc, f, dx, dy;
    dx = Graph[v].xcoord() - Graph[w].xcoord();
    dy = Graph[v].ycoord() - Graph[w].ycoord();
    75

        d = GetDistance(Graph, v, w);
    dc = d / d0;
    f = -c * log(dc);
    if (f > 500)
        f = 500;
    if (f < -500)
        f = -500;
    switch (axis)
    {
    case 0:
        return f * (dx / d);
    case 1:
        return f * (dy / d);
    }
}
double MNLmentalmap::RepulsiveForce(GRAPH<Node, Edge> &Graph,
                                    node v, node w, int axis, double c)
{
    double d, dc, f, fx, fy, dx, dy;
    dx = Graph[v].xcoord() - Graph[w].xcoord();
    dy = Graph[v].ycoord() - Graph[w].ycoord();
    d = GetDistance(Graph, v, w);
    f = c / (d * d);
    if (f > 500)
        f = 500;
    if (f < -500)
        f = -500;
    switch (axis)
    {
    case 0:
        return f * (dx / d);
    case 1:
        return f * (dy / d);
    }
}
double MNLmentalmap::InertialForce(GRAPH<Node, Edge> &Graph,
                                   node v, int axis, double c, double dkx, double dky)
{
    double dk, s, dx, dy, f;
    dx = Graph[v].xcoord() - dkx;
    dy = Graph[v].ycoord() - dky;
    dk = sqrt(pow((dx), 2) + pow((dy), 2));
    s = sqrt(pow((Graph[v].GetWidth() / 2), 2) + pow((Graph[v].GetHeight() / 2), 2));
    if (dk > s)
    {
        76

            f = -c * (pow((dk - s), 2));
        if (f > 500)
            f = 500;
        if (f < -500)
            f = -500;
        switch (axis)
        {
        case 0:
            return f * (dx / dk);
        case 1:
            return f * (dy / dk);
        }
    }
    else
    {
        return 0;
    }
}
int intersect(GRAPH<Node, Edge> &Graph, node v, node w)
{
    if ((Graph[v].xcoord() - Graph[v].GetWidth() / 2) <
            (Graph[w].xcoord() + Graph[w].GetWidth() / 2) &&
        (Graph[w].xcoord() - Graph[w].GetWidth() / 2) <
            (Graph[v].xcoord() + Graph[v].GetWidth() / 2) &&
        (Graph[v].ycoord() - Graph[v].GetHeight() / 2) <
            (Graph[w].ycoord() + Graph[w].GetHeight() / 2) &&
        (Graph[w].ycoord() - Graph[w].GetHeight() / 2) <
            (Graph[v].ycoord() + Graph[v].GetHeight() / 2))
        return 1;
    else
        return 0;
}
double MNLmentalmap::GetDistance(GRAPH<Node, Edge> &Graph, node v, node w)
{
    //dL: ノードの左上がりの対角線の傾き, dR: ノードの右上がりの対角線の傾き
    //a: ノードの中心間を結んだ線の傾き, (x1,y1): ノード v の中心, (x2,y2): ノード w の 中心
    double dLv, dRv, dLw, dRw, a, x1, x2, y1, y2; //(vx,vy),(wx,wy): ノード v,w から出ている線とノード v,w の枠との接点 double vx, vy, wx, wy;
    // 重なっていた場合
    if (intersect(Graph, v, w))
    {
        return 10;
    }
    // ノードに重なりがなかった場合 else{
    x1 = Graph[v].xcoord();
    y1 = Graph[v].ycoord();
    77

        x2 = Graph[w].xcoord();
    y2 = Graph[w].ycoord();
    // 二つのノードが縦に並んでいた時 if (x1 == x2)
    if (y1 > y2)
    {
        return (Graph[v].ycoord() - Graph[v].GetHeight() / 2) -
               (Graph[w].ycoord() + Graph[w].GetHeight() / 2);
    }
    else
    {
        return (Graph[w].ycoord() - Graph[w].GetHeight() / 2) -
               (Graph[v].ycoord() + Graph[v].GetHeight() / 2);
    }
    // 二つのノードが横に並んでいた時 if (y1 == y2)
    if (x1 > x2)
    {
        return (Graph[v].xcoord() - Graph[v].GetWidth() / 2) -
               (Graph[w].xcoord() + Graph[w].GetWidth() / 2);
    }
    else
    {
        return (Graph[w].xcoord() - Graph[w].GetWidth() / 2) -
               (Graph[v].xcoord() + Graph[v].GetWidth() / 2);
    }
    // ノードが重なってもいなく真横、真縦にも並んでいない場合 a = (y1-y2)/(x1-x2);
    dRv = -Graph[v].GetHeight() / Graph[v].GetWidth();
    dLv = Graph[v].GetHeight() / Graph[v].GetWidth();
    dRw = -Graph[w].GetHeight() / Graph[w].GetWidth();
    dLw = Graph[w].GetHeight() / Graph[w].GetWidth();
    //v は第1象現の上
    if (x1 < x2 && y1 > y2 && dRv > a)
    {
        vy = Graph[v].ycoord() - Graph[v].GetHeight() / 2;
        vx = (vy - y1 + a * x1) / a;
        //w は第3象現の上
        if (dRw < a)
        {
            wx = Graph[w].xcoord() - Graph[w].GetWidth() / 2;
            wy = a * wx + y1 - a * x1;
        }
        //w は第3象現の下 else{
        wy = Graph[w].ycoord() + Graph[w].GetHeight() / 2;
        wx = (wy - y1 + a * x1) / a;
    }
}
//v は第1象現の下
else if (x1 < x2 && y1 > y2 && dRv < a)
{
    vx = Graph[v].xcoord() + Graph[v].GetWidth() / 2;
    vy = a * vx + y1 - a * x1;
    78

        //w は第3象現の上
        if (dRw < a)
    {
        wx = Graph[w].xcoord() - Graph[w].GetWidth() / 2;
        wy = a * wx + y1 - a * x1;
    }
    //w は第3象現の下 else{
    wy = Graph[w].ycoord() + Graph[w].GetHeight() / 2;
    wx = (wy - y1 + a * x1) / a;
}
}
//v は第2象現の上
else if (x1 < x2 && y2 > y1 && dLv > a)
{
    vx = Graph[v].xcoord() + Graph[v].GetWidth() / 2;
    vy = a * vx + y1 - a * x1;
    //w は第4象現の下
    if (dLw > a)
    {
        wx = Graph[w].xcoord() - Graph[w].GetWidth() / 2;
        wy = a * wx + y1 - a * x1;
    }
    //w は第4象現の上 else{
    wy = Graph[w].ycoord() - Graph[w].GetHeight() / 2;
    wx = (wy - y1 + a * x1) / a;
}
}
//v は第2象現の下
else if (x1 < x2 && y2 > y1 && dLv < a)
{
    vy = Graph[v].ycoord() + Graph[v].GetHeight() / 2;
    vx = (vy - y1 + a * x1) / a;
    //w は第4象現の下
    if (dLw > a)
    {
        wx = Graph[w].xcoord() - Graph[w].GetWidth() / 2;
        wy = a * wx + y1 - a * x1;
    }
    //w は第4象現の上 else{
    wy = Graph[w].ycoord() - Graph[w].GetHeight() / 2;
    wx = (wy - y1 + a * x1) / a;
}
}
//v は第3象現の下
else if (x2 < x1 && y2 > y1 && dRv > a)
{
    vy = Graph[v].ycoord() + Graph[v].GetHeight() / 2;
    vx = (vy - y1 + a * x1) / a;
    //w は第1象現の上
    if (dRw > a)
    {
        wy = Graph[w].ycoord() - Graph[w].GetHeight() / 2;
        wx = (wy - y1 + a * x1) / a;
    }
    79

        //w は第1象現の下
        else
    {
        wx = Graph[w].xcoord() + Graph[w].GetWidth() / 2;
        wy = a * wx + y1 - a * x1;
    }
}
//v は第3象現の上
else if (x2 < x1 && y2 > y1 && dRv < a)
{
    vx = Graph[v].xcoord() - Graph[v].GetWidth() / 2;
    vy = a * vx + y1 - a * x1;
    //w は第1象現の上
    if (dRw > a)
    {
        wy = Graph[w].ycoord() - Graph[w].GetHeight() / 2;
        wx = (wy - y1 + a * x1) / a;
    }
    //w は第1象現の下 else{
    wx = Graph[w].xcoord() + Graph[w].GetWidth() / 2;
    wy = a * wx + y1 - a * x1;
}
}
//v は第4象現の下
else if (x2 < x1 && y1 > y2 && dLv > a)
{
    vx = Graph[v].xcoord() - Graph[v].GetWidth() / 2;
    vy = a * vx + y1 - a * x1;
    //w は第2象現の上
    if (dLw > a)
    {
        wx = Graph[w].xcoord() + Graph[w].GetWidth() / 2;
        wy = a * wx + y1 - a * x1;
    }
    //w は第2象現の下 else{
    wy = Graph[w].ycoord() + Graph[w].GetHeight() / 2;
    wx = (wy - y1 + a * x1) / a;
}
}
//v は第4象現の上
else if (x2 < x1 && y1 > y2 && dLv < a)
{
    vy = Graph[v].ycoord() - Graph[v].GetHeight() / 2;
    vx = (vy - y1 + a * x1) / a;
    //w は第2象現の上
    if (dLw > a)
    {
        wx = Graph[w].xcoord() + Graph[w].GetWidth() / 2;
        wy = a * wx + y1 - a * x1;
    }
    //w は第2象現の下 else{
    wy = Graph[w].ycoord() + Graph[w].GetHeight() / 2;
    wx = (wy - y1 + a * x1) / a;
}
80
}
return sqrt((pow((vx - wx), 2)) + (pow((vy - wy), 2)));
}
}
double MNLmentalmap::MagneticForce(GRAPH<Node, Edge> &Graph,
                                   node v, node w, int axisST, int axisXY, double c, double b,
                                   int alpha, int beta, double K)
{
    double d, dx, dy, dk, t, f, k;
    d = Graph[v].distance(Graph[w]);
    dx = (Graph[v].xcoord() - Graph[w].xcoord());
    dy = (Graph[v].ycoord() - Graph[w].ycoord());
    dk = atan2(dy, dx);
    //source のノードについて求める時は磁界の向きを逆転させる if (axisST == 1){
    if (K > 0)
        k = K - PI;
    else
        k = PI + K;
}
//target の時はそのまま else if (axisST == 2)
k = K;
// 無向磁針の時は角度の小さい方を磁界の向きにする else if (axisST ==0){
if (fabs(K - dk) > 3.0 / 2.0 * PI || PI / 2.0 >= fabs(K - dk))
    k = K;
else if (3.0 / 2.0 * PI >= fabs(K - dk) || fabs(K - dk) > PI / 2.0)
    if (K > 0)
        k = K - PI;
    else
        k = PI + K;
}
// 磁界と自分のなす角を求める if (fabs(k - dk) > PI)
t = fabs(k - dk - 2.0 * PI);
else t = fabs(k - dk);
// なす角が 0, または距離が 0 の時は磁力も 0 if (d == 0 ||t == 0)
return 0;
f = c * b * pow(d, alpha) * pow(t, beta);
if (k < 0)
{
    81

        if ((dx < 0 && dy < 0) || (dx >= 0 && dy >= 0))
    {
        if (k < -PI / 2.0 && ((PI / 2.0 >= dk && dk > PI + k) || (k < dk && dk < -PI / 2.0)))
        {
            if (axisXY == 1)
            {
                return -f * (fabs(dy) / d);
            }
            else
            {
                return f * (fabs(dx) / d);
            }
        }
        else
        {
            if (axisXY == 1)
            {
                return f * (fabs(dy) / d);
            }
            else
            {
                return -f * (fabs(dx) / d);
            }
        }
    }
    else if ((dx < 0 && dy >= 0) || (dx >= 0 && dy < 0))
    {
        if (k > -PI / 2.0 && ((-PI / 2.0 < dk && dk < k) || (PI / 2.0 < dk && dk < PI + k)))
        {
            if (axisXY == 1)
            {
                return f * (fabs(dy) / d);
            }
            else
            {
                return f * (fabs(dx) / d);
            }
        }
        else
        {
            if (axisXY == 1)
            {
                return -f * (fabs(dy) / d);
            }
            else
            {
                return -f * (fabs(dx) / d);
            }
        }
    }
}
if (k >= 0)
{
    if ((dx < 0 && dy < 0) || (dx >= 0 && dy >= 0))
    {
        if (k < PI / 2.0 && ((PI / 2.0 > dk && dk > k) || (k - PI < dk && dk < -PI / 2.0)))
        {
            if (axisXY == 1)
            {
                return f * (fabs(dy) / d);
            }
            else
            {
                return -f * (fabs(dx) / d);
            }
        }
        else
        {
            if (axisXY == 1)
            {
                82

                    return -f *
                    (fabs(dy) / d);
            }
            else
            {
                return f * (fabs(dx) / d);
            }
        }
    }
    else if ((dx < 0 && dy >= 0) || (dx >= 0 && dy < 0))
    {
        if (k > PI / 2.0 && ((-PI / 2.0 < dk && dk < k - PI) || (PI / 2.0 < dk && dk < k)))
        {
            if (axisXY == 1)
            {
                return -f * (fabs(dy) / d);
            }
            else
            {
                return -f * (fabs(dx) / d);
            }
        }
        else
        {
            if (axisXY == 1)
            {
                return f * (fabs(dy) / d);
            }
            else
            {
                return f * (fabs(dx) / d);
            }
        }
    }
}
}
// ノードを円周上に初期配置する
int MNLmentalmap::init(GRAPH<Node, Edge> &Graph)
{
    int NodeNum;
    int ox = 300, oy = 300, r;
    double angle, da;
    node nd;
    node_array<double> xp(Graph), yp(Graph);
    NodeNum = Graph.number_of_nodes(); //全ノード数 angle = 6.28 / NodeNum; //角度差
    r = NodeNum * 5 + 40;              //半径
    da = 0.0;                          //角度
    forall_nodes(nd, Graph)
    {
        xp[nd] = r * cos(da) + ox;
        yp[nd] = r * sin(da) + oy;
        Graph[nd] = Node(Graph[nd].GetNodeId(), Graph[nd].GetNodeType(),
                         xp[nd], yp[nd], Graph[nd].GetWidth(), Graph[nd].GetHeight());
        da += angle;
    }
    83
}
StraightLine.C
#include "EdgeRouter.h"
#include <math.h>
#include <LEDA/line.h>
    void
    StraightLine::EdgeLayout(GRAPH<Node, Edge> &Graph)
{
    edge e;
    Node N1, N2;
    Edge E;
    int i;
    point sp1, sp2, sp3, sp4, ep1, ep2, ep3, ep4, sp, ep;
    polygon *spg, *epg;
    segment *el1, smt;
    list<point> pl, Ispl1, Ispl2, eline;
    forall_edges(e, Graph)
    {
        N1 = Graph[Graph.source(e)];
        N2 = Graph[Graph.target(e)];
        E = Graph[e];
        sp1 = point(N1.xcoord() - N1.GetWidth() / 2, N1.ycoord() - N1.GetHeight() / 2);
        sp2 = point(N1.xcoord() + N1.GetWidth() / 2, N1.ycoord() - N1.GetHeight() / 2);
        sp3 = point(N1.xcoord() + N1.GetWidth() / 2, N1.ycoord() + N1.GetHeight() / 2);
        sp4 = point(N1.xcoord() - N1.GetWidth() / 2, N1.ycoord() + N1.GetHeight() / 2);
        ep1 = point(N2.xcoord() - N2.GetWidth() / 2, N2.ycoord() - N2.GetHeight() / 2);
        ep2 = point(N2.xcoord() + N2.GetWidth() / 2, N2.ycoord() - N2.GetHeight() / 2);
        ep3 = point(N2.xcoord() + N2.GetWidth() / 2, N2.ycoord() + N2.GetHeight() / 2);
        ep4 = point(N2.xcoord() - N2.GetWidth() / 2, N2.ycoord() + N2.GetHeight() / 2);
        pl.append(sp1);
        pl.append(sp2);
        pl.append(sp3);
        pl.append(sp4);
        spg = new polygon(pl);
        pl.clear();
        pl.append(ep1);
        pl.append(ep2);
        pl.append(ep3);
        pl.append(ep4);
        epg = new polygon(pl);
        pl.clear();
        Ispl1 = spg->intersection(segment(N1, N2));
        84

            if (Ispl1.size() == 0)
        {
            cout << "Ispll.size = 0" << endl;
            Ispl1.push(point(N1.xcoord(), N1.ycoord()));
        }
        eline.append(Ispl1.pop());
        Ispl2 = epg->intersection(segment(N1, N2));
        if (Ispl2.size() == 0)
        {
            cout << "Ispl2.size = 0" << endl;
            Ispl2.push(point(N2.xcoord(), N2.ycoord()));
        }
        eline.append(Ispl2.pop());
        Graph[e].SetEdgeLine(eline);
        eline.clear();
    }
}
3DspringLayouter.C
#include "NodePlacer.h"
#include <math.h>
#include <LEDA/node_matrix.h>
#define ITERATION 5000
#define PI M_PI
#define DC1 30.0
#define DC2 600.0
#define DC3 20000.0
//π //スプリング定数
//スプリングの長さ
// 非隣接頂点間定数 (使ってない)
#define DC4 5
#define DC5 0.01
#define DC6 0.01
#define DC7 0.01
#define DC8 10.0
#define DC9 1
#define DC10 1
#define DC11 0
#define DC12 PI / 4.0
#define DC13 PI / 2.0
#define DC14 0.1
    //微小移動量定数
    // 関連エッジの磁力定数 // 集約エッジの磁力定数 // 継承エッジの磁力定数
    // 磁場の強さ
    // 辺の長さの回転力への影響 // 角度の回転力への影響
    // 関連エッジの角度
    // 集約エッジの角度
    // 継承エッジの角度
    //InertailForce係数
    extern node
    get_node_fromid(GRAPH<Node, Edge> &g, string id);
void SpringNodePlacer::NodeLayout(GRAPH<Node, Edge> &Graph)
{
    node n1, n2, n3;
    edge e;
    int i;
    double x, y, z, w, h, d, d1, d2, d3;
    85

        double nx = 0,
               ny = 0, nz = 0;
    node_array<double> forcex(Graph), forcey(Graph), forcez(Graph);
    //init(Graph);
    node_array<double> C4(Graph);
    node_array<double> C5(Graph);
    node_array<double> CX(Graph);
    node_array<double> CY(Graph);
    node_array<double> CZ(Graph);
    node_matrix<double> C1(Graph);
    node_matrix<double> C2(Graph);
    node_matrix<double> C3(Graph);
    // 定数の決定 forall_nodes(n1,Graph){
    forall_nodes(n2, Graph)
    {
        d1 = sqrt(pow((Graph[n1].GetWidth() / 2), 2) + pow((Graph[n1].GetHeight() / 2), 2));
        d2 = sqrt(pow((Graph[n2].GetWidth() / 2), 2) + pow((Graph[n2].GetHeight() / 2), 2));
        d3 = sqrt(pow((Graph[n2].GetDepth() / 2), 2) + pow((Graph[n2].GetDepth() / 2), 2));
        // スプリング定数 C1(n1,n2) = DC1;
        // スプリングの自然長 C2(n1,n2) = DC2;
        // 非隣接頂点間定数
        C3(n1, n2) = DC3;
    }
    // 微小移動量定数
    C4[n1] = DC4;
    C5[n1] = DC14;
    CX[n1] = Graph[n1].xcoord();
    CY[n1] = Graph[n1].ycoord();
    CZ[n1] = Graph[n1].zcoord();
}
forall_nodes(n1, Graph){
    cout << Graph[n1].GetNodeId()}
    << ":(" << Graph[n1].xcoord() - Graph[n1].GetWidth() / 2 << ","
    << Graph[n1].ycoord() - Graph[n1].GetHeight() / 2
    << Graph[n1].zcoord() - Graph[n1].GetDepth() / 2 << ")"
    << ":(" << Graph[n1].GetWidth() << ","
    << Graph[n1].GetHeight() << ","
    << Graph[n1].GetDepth() << ")" << endl;
86

    for (i = 0; i < ITERATION; i++)
{
    forall_nodes(n1, Graph)
    {
        forcex[n1] = 0;
        forcey[n1] = 0;
        forcez[n1] = 0;
        forall_nodes(n2, Graph)
        {
            int flag = 0;
            if (n1 != n2)
            {
                forall_inout_edges(e, n1)
                {
                    if (Graph.opposite(n1, e) == n2 && Graph.opposite(n2, e) == n1)
                    { //n1 と n2 が辺 e で隣接していた時スプリングによる力を計算
                        forcex[n1] = forcex[n1] forcey[n1] = forcey[n1] forcez[n1] = forcez[n1] flag = 1;
                    }
                }
                // 隣接していない時斥力を計算 if (flag == 0){
                +AttractiveForce(Graph, n1, n2, 0, C1[n1][n2], C2[n1][n2]);
                +AttractiveForce(Graph, n1, n2, 1, C1[n1][n2], C2[n1][n2]);
                +AttractiveForce(Graph, n1, n2, 2, C1[n1][n2], C2[n1][n2]);
                forcex[n1] = forcex[n1] + RepulsiveForce(Graph, n1, n2, 0, C3[n1][n2]);
                forcey[n1] = forcey[n1] + RepulsiveForce(Graph, n1, n2, 1, C3[n1][n2]);
                forcez[n1] = forcez[n1] + RepulsiveForce(Graph, n1, n2, 2, C3[n1][n2]);
            }
        }
    }
}
// ノード n1 を移動する forall_nodes(n1,Graph){
x = Graph[n1].xcoord();
y = Graph[n1].ycoord();
z = Graph[n1].zcoord();
x = x + C4[n1] * forcex[n1];
y = y + C4[n1] * forcey[n1];
z = z + C4[n1] * forcez[n1];
Graph[n1] = Node(Graph[n1].GetNodeId(), Graph[n1].GetNodeType(), x, y, z,
                 Graph[n1].GetWidth(), Graph[n1].GetHeight(), Graph[n1].GetDepth());
}
}
cout << "┌─── 調整前の座標と大きさ ───┐ " << endl;
forall_nodes(n1, Graph)
{
    cout << Graph[n1].GetNodeId()
         << ":(" << Graph[n1].xcoord() - Graph[n1].GetWidth() / 2 << ","
         << Graph[n1].ycoord() - Graph[n1].GetHeight() / 2 << ","
         << Graph[n1].zcoord() - Graph[n1].GetDepth() / 2 << ")" 87

         << ":(" << Graph[n1].GetWidth() << ","
         << Graph[n1].GetHeight() << ","
         << Graph[n1].GetDepth() << ")" << endl;
}
cout << "└─────────────────┘ " << endl; // 全体の位置の調整
ShiftGraph(Graph);
cout << "┌─── 調整後の座標と大きさ ───┐ " << endl;
forall_nodes(n1, Graph)
{
    cout << Graph[n1].GetNodeId()
         << ":(" << Graph[n1].xcoord() - Graph[n1].GetWidth() / 2 << ","
         << Graph[n1].ycoord() - Graph[n1].GetHeight() / 2 << ","
         << Graph[n1].zcoord() - Graph[n1].GetDepth() / 2 << ")"
         << ":(" << Graph[n1].GetWidth() << ","
         << Graph[n1].GetHeight() << ","
         << Graph[n1].GetDepth() << ")" << endl;
}
cout << "└─────────────────┘ " << endl;
cout << "SpringLayout-end" << endl;
}
double SpringNodePlacer::AttractiveForce(GRAPH<Node, Edge> &Graph,
                                         node v, node w, int axis, double c, double d0)
{
    double d, dc, f, dx, dy, dz;
    dx = Graph[v].xcoord() - Graph[w].xcoord();
    dy = Graph[v].ycoord() - Graph[w].ycoord();
    dz = Graph[v].zcoord() - Graph[w].zcoord();
    d = Graph[v].distance(Graph[w]);
    dc = d / d0;
    f = -c * log(dc);
    if (f > 500)
        f = 500;
    if (f < -500)
        f = -500;
    switch (axis)
    {
    case 0:
        return f * (dx / d);
    case 1:
        return f * (dy / d);
    case 2:
        return f * (dz / d);
    }
}
88

    double
    SpringNodePlacer::RepulsiveForce(GRAPH<Node, Edge> &Graph,
                                     node v, node w, int axis, double c)
{
    double d, dc, f, dx, dy, dz;
    dx = Graph[v].xcoord() - Graph[w].xcoord();
    dy = Graph[v].ycoord() - Graph[w].ycoord();
    dz = Graph[v].zcoord() - Graph[w].zcoord();
    d = Graph[v].distance(Graph[w]);
    f = c / (d * d);
    if (f > 500)
        f = 500;
    if (f < -500)
        f = -500;
    switch (axis)
    {
    case 0:
        return f * (dx / d);
    case 1:
        return f * (dy / d);
    case 2:
        return f * (dz / d);
    }
}
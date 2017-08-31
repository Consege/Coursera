function [mydistance,mypath] = mydijkstra(a,sb,db);
%����:a- �ڽӾ���; a(i,j)- i��j�ľ���
%sb- ���ı��, db- �յ�ı��
%���:mydistance- ���·�ľ��� , mypath- ���·��·��

n = size(a,1);visited(1:n) = 0 ;
distance(1:n) = inf ; distance(sb) = 0 ; %��㵽���������ĳ�ʼ��
visited(sb) = 1;u =sb; %uΪ���µ�P��Ŷ���
parent(1:0) = 0 ; %ǰ������ĳ�ʼ��
for i = 1 : n-1
    id = find(visited == 0)
    for v = id
        if(a(u,v)+distance(u)<distance(v))
            distance(v) = a(u,v)+distance(u);
            parent(v) = u ;
        end
        temp = distance ;
        temp(visited == 1) = inf ; %�����Ѿ����뼯�ϵĵ�ľ��뻻������
        [t,u] = min(temp) ;% �Ҿ�����С�ĵ�
        visited(u) = 1 ;%����Ѿ���ŵĶ���
    end
end
mypath = [];
if parent(db) ~= 0 
    t=db ; mypath = [db] ;
    while t ~= sb
        P = parent(t) ;
        mypath = [P  mypath] ;
        t = p ;
    end
end
mydistance = distance(db);

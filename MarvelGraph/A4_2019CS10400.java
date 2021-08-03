//Code submitted by Shrey J. Patel, 2019CS10400 from COL106 Group 9


import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;


//Vertex information
class Vertex{
    String label;                  //Name of the vertex
    int degree;                    //Number of neighbours
    int weightedDegree;            //Total sum of all edge weights

    public Vertex(String s){
        this.label = s;
        this.degree = 0;
        this.weightedDegree = 0;
    }
}

public class A4_2019CS10400{

    private ArrayList<Vertex> nodeList;                                 //Index to Label matching
    private HashMap<String,Integer> nodeMap;                            //Label to Index matching
    private HashMap<String,HashMap<String,Integer>> adjList;            //Adjacency List as a HashMap
    private int n;                                                      //No of vertices
    private int m;                                                      //No of edges

    public A4_2019CS10400 (FileReader csvNodes,FileReader csvEdges){

        this.nodeList = new ArrayList<Vertex>();
        this.nodeMap = new HashMap<String,Integer>();
        this.adjList = new HashMap<String,HashMap<String,Integer>>();
        this.n = 0;
        this.m = 0;

        //Reading Nodes
        BufferedReader bReaderNodes = new BufferedReader(csvNodes);     //File Reader

        String next="";
        try{
            next=bReaderNodes.readLine();                               //Skipping first line

            while((next = bReaderNodes.readLine()) != null){
                ArrayList<String> newInput = splitLine(next);           //Splitting the current line into two strings
                if(newInput.size()==2){
                    Vertex v = new Vertex(newInput.get(0));

                    //Adding nodes to local list
                    this.nodeList.add(v);
                    this.nodeMap.put(newInput.get(0),n);
                    this.adjList.put(newInput.get(0),new HashMap<String,Integer>());
                    n++;
                }else{
                    throw new Exception();
                }
            }

            bReaderNodes.close();

        }catch(Exception io){
            System.err.println("Invalid Input");
        }




        //Reading Edges
        BufferedReader bReaderEdges = new BufferedReader(csvEdges);

        next="";
        try{
            next=bReaderEdges.readLine();                               //Skipping first line

            while((next = bReaderEdges.readLine()) != null){
                ArrayList<String> newInput = splitLine(next);
                if(newInput.size()==3){                                 //Splitting the current line into three strings
                    int k = Integer.valueOf(newInput.get(2));

                    //Updating adjacency list
                    adjList.get(newInput.get(0)).put(newInput.get(1),k);
                    adjList.get(newInput.get(1)).put(newInput.get(0),k);
                    
                    //Updating Node parameters
                    Vertex u = nodeList.get(nodeMap.get(newInput.get(0)));
                    Vertex v = nodeList.get(nodeMap.get(newInput.get(1)));
                    u.degree = u.degree + 1;
                    v.degree = v.degree + 1;
                    u.weightedDegree = u.weightedDegree + k;
                    v.weightedDegree = v.weightedDegree + k;
                    m++;
                }else{
                    throw new Exception();
                }
            }

            bReaderEdges.close();

        }catch(Exception io){
            System.err.println("Invalid Input");
        }

    }

    //Custom string splitter
    public ArrayList<String> splitLine(String line){
        ArrayList<String> list = new ArrayList<String>();
        boolean isOpen = false;
        int i=0;
        String currentString = "";
        while(i<line.length()){
            if(line.charAt(i)!=',' && line.charAt(i)!='"'){
                currentString = currentString + Character.toString(line.charAt(i));
            }else{
                if(line.charAt(i)=='"'){
                    if(isOpen){
                        if(i!=line.length()-1){
                            if(line.charAt(i+1)==','){
                                if(!currentString.isEmpty()){
                                    list.add(currentString);
                                    currentString = "";
                                }
                                isOpen = false;
                                i++;
                            }else{
                                currentString = currentString + Character.toString(line.charAt(i));
                            }
                        }
                    }else{
                        if(!currentString.isEmpty()){
                            list.add(currentString);
                            currentString = "";
                        }
                        isOpen = true;
                    }
                }else{
                    if(isOpen){
                        currentString = currentString + Character.toString(line.charAt(i));
                    }else{
                        if(!currentString.isEmpty()){
                            list.add(currentString);
                            currentString = "";
                        }
                    }
                }
            }
            i++;
        }
        if(!currentString.isEmpty()){
            list.add(currentString);
        }
        return list;
    }



    //Finds average degree 
    public void avg(){
        double mean = (2.0*m)/(n);
        System.out.println(String.format("%.2f",mean));
    }




    //Sorting based on total weighted degree
    public void printRank(){
        ArrayList<Vertex> rankList = nodeList;
        int j=rankList.size();
        qSort(rankList,0,j-1);
        int i=0;
        while(i<j-1){
            System.out.print(rankList.get(i).label+",");
            i++;
        }
        System.out.println(rankList.get(i).label);
    }

    //QuickSort based on the order of weighted degrees
    public void qSort(ArrayList<Vertex> rankList,int low,int high){
        if(low<high){
            int p = partition(rankList,low,high);
            qSort(rankList, low, p-1);
            qSort(rankList, p+1, high);
        }
    }

    public int partition(ArrayList<Vertex> rankList,int low,int high){
        int r = (int)(low + (high-low)*Math.random());
        Vertex temp2=rankList.get(r);
        rankList.set(r, rankList.get(low));
        rankList.set(low, temp2);
        Vertex x = rankList.get(low);
        int i = low;
        for(int j=low+1;j<=high;j++){
            if(rank_comp(rankList.get(j), x)>0){
                i++;
                Vertex temp=rankList.get(i);
                rankList.set(i, rankList.get(j));
                rankList.set(j, temp);
            }
        }
        Vertex temp=rankList.get(i);
        rankList.set(i, rankList.get(low));
        rankList.set(low, temp);
        return i;
    }

    //Rank comparator
    public int rank_comp(Vertex a,Vertex b){
        if(a.weightedDegree<b.weightedDegree){
            return -1;
        }else{
            if(a.weightedDegree>b.weightedDegree){
                return 1;
            }else{
                return (a.label).compareTo(b.label);
            }
        }
    }




    //Finds connected components
    public void traversal(){
        ArrayList<Boolean> visited = new ArrayList<Boolean>();
        for(int i=0;i<n;i++){
            visited.add(false);
        }
        ArrayList<ArrayList<String>> componentList = new ArrayList<ArrayList<String>>();
        for(int i=0;i<n;i++){
            if(!visited.get(i)){
                ArrayList<String> component = new ArrayList<String>();
                DFS(i,visited,component);
                lexSort(component,0,component.size()-1);
                componentList.add(component);
            }
        }
        completeSort(componentList,0,componentList.size()-1);
        for(int i=0;i<componentList.size();i++){
            int j=0;
            while(j<componentList.get(i).size()-1){
                System.out.print(componentList.get(i).get(j) + ",");
                j++;
            }
            System.out.println(componentList.get(i).get(j));
        }
    }

    //Depth First Search
    public void DFS(int index,ArrayList<Boolean> visited,ArrayList<String> component){
        visited.set(index,true);
        component.add(nodeList.get(index).label);
        HashMap<String,Integer>  searchMap = adjList.get(nodeList.get(index).label);
        for(String s:searchMap.keySet()){
            int index2 = nodeMap.get(s);
            if(!visited.get(index2)){
                DFS(index2,visited,component);
            }
        }
    }

    //Lexicographic sorting of each component. Inside each component, strings are arranged in reverse lexicographic order
    public void lexSort(ArrayList<String> component,int low,int high){
        if(low<high){
            int p = partition2(component,low,high);
            lexSort(component, low, p-1);
            lexSort(component, p+1, high);
        }
    }

    public int partition2(ArrayList<String> component,int low,int high){
        int r = (int)(low + (high-low)*Math.random());
        String temp2 = component.get(r);
        component.set(r,component.get(low));
        component.set(low, temp2);
        String x = component.get(low);
        int i = low;
        for(int j=low+1;j<=high;j++){
            if((component.get(j)).compareTo(x)>0){
                i++;
                String temp=component.get(i);
                component.set(i, component.get(j));
                component.set(j, temp);
            }
        }
        String temp=component.get(i);
        component.set(i, component.get(low));
        component.set(low, temp);
        return i;
    }

    //Sorting of components based on length
    public void completeSort(ArrayList<ArrayList<String>> componentList,int low,int high){
        if(low<high){
            int p = partition3(componentList,low,high);
            completeSort(componentList, low, p-1);
            completeSort(componentList, p+1, high);
        }
    }

    public int partition3(ArrayList<ArrayList<String>> componentList,int low,int high){
        int r = (int)(low + (high-low)*Math.random());
        ArrayList<String> temp2=componentList.get(r);
        componentList.set(r, componentList.get(low));
        componentList.set(low, temp2);
        ArrayList<String> x = componentList.get(low);
        int i = low;
        for(int j=low+1;j<=high;j++){
            if(comp(componentList.get(j),x)>0){
                i++;
                ArrayList<String> temp=componentList.get(i);
                componentList.set(i, componentList.get(j));
                componentList.set(j, temp);
            }
        }
        ArrayList<String> temp=componentList.get(i);
        componentList.set(i, componentList.get(low));
        componentList.set(low, temp);
        return i;
    }

    //Comparator for components for the purpose of sorting. Larger components appear before smaller ones and if they are same,
    //they follow descending lexicographic error. 
    public int comp(ArrayList<String> a,ArrayList<String> b){
        if(a.size()<b.size()){
            return -1;
        }else{
            if(a.size()>b.size()){
                return 1;
            }else{
                return (a.get(0)).compareTo(b.get(0));
            }
        }
    }

    public static void main(String[] args){
        try{
            A4_2019CS10400 newGraph = new A4_2019CS10400(new FileReader(args[0]),new FileReader(args[1]));
            if(args[2].equals("average")){
                newGraph.avg();
            }else if(args[2].equals("rank")){
                newGraph.printRank();
            }else{
                newGraph.traversal();
            }
        }catch(FileNotFoundException f){
            System.err.println("File Not Found");
        }
    }
}

import java.util.Scanner;
import java.util.ArrayList;

class DisjointSet {
  ArrayList<Integer> parents;
  ArrayList<Integer> ranks;

  public Integer findParent(Integer i){
    if(parents.get(i) == i)
      return i; 

    parents.set(i,findParent(parents.get(i)));
    return parents.get(i);
  }

  public void unionSet(Integer i,Integer j){
    if(!isSameSet(i,j)){
      Integer parentA =  findParent(i);
      Integer parentB = findParent(j);

      if(ranks.get(parentA) > ranks.get(parentB)){
        parents.set(parentB,parentA);
      }
      else{
        parents.set(parentA,parentB); 
        
        if(ranks.get(parentA) == ranks.get(parentB)){
          ranks.set(parentB,ranks.get(parentB)+1);
        }
      }
    }
  }

  public Boolean isSameSet(Integer i, Integer j){
    return findParent(i) == findParent(j);
  }

  public DisjointSet(Integer n){
    parents = new ArrayList<Integer>();
    ranks = new ArrayList<Integer>();

    for(int i=0;i<n;i++){
      parents.add(i);
      ranks.add(0);
    }
  }
}

public class Main {

  public static void main(String[] args){
    Scanner input = new Scanner(System.in);  
    Integer cases = input.nextInt();

    while(cases > 0){
      Integer computersNumber = input.nextInt();
      input.nextLine();
    
      DisjointSet set = new DisjointSet(computersNumber);

      executeInstructions(input, set);
      cases--;

      if(cases > 0){
        System.out.println();
      }
    }
  }

  public static void executeInstructions(Scanner input, DisjointSet set){
    String instruction;
    Integer questions, rightQuestions;
    questions = rightQuestions = 0;

    while(input.hasNextLine() && !((instruction = input.nextLine()).equals(""))){
      String[] queryOrJoin = instruction.split(" ");
      Integer computerA = Integer.parseInt(queryOrJoin[1]);
      Integer computerB = Integer.parseInt(queryOrJoin[2]);

      if(queryOrJoin[0].equals("c")){
        set.unionSet(computerA-1,computerB-1);
      }
      else{
        questions++;

        if(set.isSameSet(computerA-1,computerB-1)){
          rightQuestions++;
        }
      }
    }

    System.out.println(rightQuestions + "," + (questions-rightQuestions));
  }

}

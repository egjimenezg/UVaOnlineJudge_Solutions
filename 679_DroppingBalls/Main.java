import java.util.Scanner;
import java.util.stream.IntStream;
import java.io.PrintWriter;
import java.io.BufferedWriter;
import java.io.OutputStreamWriter;

public class Main {

  public static void main(String... args){
    Scanner scanner = new Scanner(System.in);
    StringBuilder answer = new StringBuilder();

    PrintWriter printWriter = new PrintWriter(new BufferedWriter(
      new OutputStreamWriter(System.out)));

    IntStream.range(0, scanner.nextInt()).forEach( n -> {
      Integer position = getBallPosition(scanner.nextInt(), scanner.nextInt());
      answer.append(position);
      answer.append("\n");
    });

    scanner.close();

    printWriter.println(answer.toString().trim());
    printWriter.close();
  }

  public static Integer getBallPosition(Integer maxDepth, Integer ballSwaps){
    Integer position = 1; 

    for(Integer depth=2; depth<= maxDepth; depth++){
      if(isOdd(ballSwaps)){
        ballSwaps = 1+(ballSwaps/2);
        position *= 2;
      } else {
        ballSwaps /= 2;
        position = (position*2)+1;
      }
    }

    return position; 
  }

  public static boolean isOdd(Integer n){
    return (n & 1) == 1;
  }

}

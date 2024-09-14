package SistemaBiblioteca.src;

import java.util.ArrayList;
import java.util.List;

import SistemaBiblioteca.src.components.livros.Livro;
import SistemaBiblioteca.src.components.usuarios.Grad;
import SistemaBiblioteca.src.components.usuarios.PosGrad;
import SistemaBiblioteca.src.components.usuarios.Professor;
import SistemaBiblioteca.src.frontend.Biblioteca;

public class InitFabrica {
    public static void initTeste(){
        Biblioteca biblioteca = Biblioteca.obterInstancia();

        biblioteca.adicionarUsuario(new Grad(123, "João da Silva"));
        biblioteca.adicionarUsuario(new PosGrad(456, "Luiz Fernando Rodrigues"));
        biblioteca.adicionarUsuario(new Grad(789,"Pedro Paulo"));
        biblioteca.adicionarUsuario(new Professor(100, "Carlos Lucena"));

        List<String> autores1 = new ArrayList<String>();
        autores1.add("Ian Sommervile");
        Livro liv1 = new Livro(100, "Engenharia de Software", "AddisonWesley", autores1, "6ª", 2000);
        liv1.adicionarExemplar(1);
        liv1.adicionarExemplar(2);

        List<String> autores2 = new ArrayList<String>();
        autores2.add("Grady Booch");
        autores2.add("James Rumbaugh");
        autores2.add("Ivar Jacobson");
        Livro liv2 = new Livro(101, "UML – Guia do Usuário", "Campus", autores2, "7ª", 2000);
        liv2.adicionarExemplar(3);

        List<String> autores3 = new ArrayList<String>();
        autores3.add("Steve McConnell");
        Livro liv3 = new Livro(200, "Code Complete", "Microsoft Press", autores3, "2ª", 2014);
        liv3.adicionarExemplar(4);

        List<String> autores4 = new ArrayList<String>();
        autores4.add("Robert Martin");
        Livro liv4 = new Livro(201, "Agile Software Development, Principles, Patterns, and Practices",
                             "Prentice Hall", autores4, "1ª", 2002);
        liv4.adicionarExemplar(5);

        List<String> autores5 = new ArrayList<String>();
        autores5.add("Martin Fowler");
        Livro liv5 = new Livro(300, "Refactoring:Improving the Design of Existing Code",
                             "AddisonWesley Professional", autores5, "1ª", 1999);
        liv5.adicionarExemplar(6);
        liv5.adicionarExemplar(7);

        List<String> autores6 = new ArrayList<String>();
        autores6.add("Norman Fenton");
        autores6.add("James Bieman");
        Livro liv6 = new Livro(301, "Software Metrics: A Rigorous and Practical Approach",
                             "CRC Press", autores6, "3ª", 2014);
        
        List<String> autores7 = new ArrayList<String>();
        autores7.add("Erich Gamma");
        autores7.add("Richard Helm");
        autores7.add("Ralph Johnson");
        autores7.add("John Vlissides");
        Livro liv7 = new Livro(400, "Design Patterns: Elements of Reusable Object-Oriented Software",
                             "AddisonWesley Professional", autores7, "1ª", 1994);
        liv7.adicionarExemplar(8);
        liv7.adicionarExemplar(9);

        List<String> autores8 = new ArrayList<String>();
        autores8.add("Martin Fowler");
        Livro liv8 = new Livro(401, "UML Distilled: A Brief Guide to the Standard Object Modeling Language",
                             "AddisonWesley Professional", autores8, "3ª", 2003);


        biblioteca.adicionarLivro(liv1);
        biblioteca.adicionarLivro(liv2);
        biblioteca.adicionarLivro(liv3);
        biblioteca.adicionarLivro(liv4);
        biblioteca.adicionarLivro(liv5);
        biblioteca.adicionarLivro(liv6);
        biblioteca.adicionarLivro(liv7);
        biblioteca.adicionarLivro(liv8);
    }
}

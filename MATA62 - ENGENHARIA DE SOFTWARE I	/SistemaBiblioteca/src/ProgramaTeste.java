package SistemaBiblioteca.src;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

import SistemaBiblioteca.src.components.livros.Livro;
import SistemaBiblioteca.src.components.usuarios.ObservadorReserva;
import SistemaBiblioteca.src.components.usuarios.Professor;

public class ProgramaTeste {
    public static void main(String[] args) throws Exception {
        LocalDateTime now = LocalDateTime.now(); 
        System.out.println(now);
        int a = 3;
        LocalDateTime after = now.plusDays(a);
        System.out.println(now.isBefore(after));
        Professor prof = new Professor(a, null);
        List<Professor> profs = new ArrayList<Professor>();
        //profs.set(0, prof);
        System.out.println(prof.getLimiteEmprestimo());
        /* Livro li = new Livro();
        li.registraObservador(prof);
        li.notificaObservadores();
        System.out.println(prof.getQntNotificacoes());
        li.removeObservador(prof);
        li.notificaObservadores();
        System.out.println(prof.getQntNotificacoes()); */
    }
}

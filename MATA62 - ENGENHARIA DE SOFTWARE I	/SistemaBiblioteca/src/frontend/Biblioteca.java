package SistemaBiblioteca.src.frontend;

import java.util.ArrayList;
import java.util.List;

import SistemaBiblioteca.src.components.livros.Livro;
import SistemaBiblioteca.src.components.usuarios.ObservadorReserva;
import SistemaBiblioteca.src.components.usuarios.Professor;
import SistemaBiblioteca.src.components.usuarios.Usuario;

//----------------------------------------------------------------
//Fachada
public class Biblioteca {
    private static Biblioteca instancia;
    private List<Livro> livros = new ArrayList<Livro>();
    private List<Usuario> usuarios = new ArrayList<Usuario>();

    private Biblioteca(){}

    public static Biblioteca obterInstancia(){
        if(instancia == null){
            instancia = new Biblioteca();   
        }
        return instancia;
    }

    public Livro consultarLivro(int livroId){
        Livro livro = null;

        for (int index = 0; index < livros.size(); index++) { 
            if (livroId == livros.get(index).getId()) {
                livro = livros.get(index);
                return livro;
            }
        } 
        return livro;
    }

    public int consultarNotificacoes(int usuarioId) {
        Professor usuario = (Professor) consultarUsuario(usuarioId);
        return usuario.getQntNotificacoes();
    }

    public Usuario consultarUsuario(int usuarioId){
        Usuario usuario = null;

        for (int index = 0; index < usuarios.size(); index++) { 
            if (usuarioId == usuarios.get(index).getID()) {
                usuario = usuarios.get(index);
                return usuario;
            }
        } 
        return usuario;
    }

    public boolean devolverLivro(int usuarioId, int livroId) {
        Usuario usuario = consultarUsuario(usuarioId);
        Livro livro = consultarLivro(livroId);
        return usuario.concluirEmprestimo(livro);
    }

    public boolean fazerReserva(int usuarioId, int livroId) {
        Usuario usuario = consultarUsuario(usuarioId);
        Livro livro = consultarLivro(livroId);
        return usuario.realizarReserva(livro);
    }

    public boolean realizarEmprestimo(int usuarioId, int livroId) {
        Usuario usuario = consultarUsuario(usuarioId);
        Livro livro = consultarLivro(livroId);
        return usuario.realizarEmprestimo(livro);   
    }

    public void registrarObservador(int usuarioId, int livroId) {
        Usuario usuario = consultarUsuario(usuarioId);
        Livro livro = consultarLivro(livroId);
        livro.registraObservador((ObservadorReserva) usuario);    
    }

    public void adicionarLivro(Livro livro){
        livros.add(livro);
    }

    public void adicionarUsuario(Usuario usuario){
        usuarios.add(usuario);
    }
}

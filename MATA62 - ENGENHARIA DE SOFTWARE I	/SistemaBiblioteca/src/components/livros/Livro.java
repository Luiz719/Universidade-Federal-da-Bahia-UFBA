package SistemaBiblioteca.src.components.livros;

import java.util.ArrayList;
import java.util.List;

import SistemaBiblioteca.src.components.Reserva;
import SistemaBiblioteca.src.components.usuarios.ObservadorReserva;

public class Livro implements ILivroObservavel{
    private int coDlivro;
    private String titulo;
    private String editora;
    private List<String> autores;
    private String edicao;
    private int anoPublicacao;
    private List<ObservadorReserva> observadores = new ArrayList<ObservadorReserva>();
    private List<LivroExemplar> exemplares = new ArrayList<LivroExemplar>();
    private List<Reserva> reservas = new ArrayList<Reserva>();
    private EstadoLivro estado;

    public Livro(int codLivro, String titulo, String editora, List<String> autores, String edicao, int anoPublicacao){
        this.coDlivro = codLivro;
        this.titulo = titulo;
        this.editora = editora;
        this.anoPublicacao = anoPublicacao;
        this.edicao = edicao;
        this.autores = autores;
        this.estado = new ExemplarIndisponivel();
    }

    public boolean podeSerEmprestado(){
        return estado.podeSerEmprestado(this);
    }

    public void adicionarReserva(Reserva novaReserva){
        reservas.add(novaReserva);
        if(reservas.size() >= 2) notificaObservadores();
    }

    public void adicionarExemplar(int codExemplar){
        LivroExemplar novoExemplar = new LivroExemplar(this, codExemplar);
        exemplares.add(novoExemplar);
        setEstadoExemplar(new ExemplarDisponivel());
    }

    public int getNumeroReservas(){
        return reservas.size();
    }

    public int getNumeroExemplares(){
        return exemplares.size();
    }

    public LivroExemplar getExemplar(int index) {
        return this.exemplares.get(index);
    }

    public Reserva getReserva(int index) {
        return this.reservas.get(index);
    }

    public void removeReserva(int codUsu){
        for (int obj = 0; obj < reservas.size(); obj++) { 
            if(codUsu == reservas.get(obj).getCodUsuario()){
                reservas.remove(obj);
            }
        } 
    }

    public boolean temMaisReservasQueExemplares(){
        return reservas.size() >= getNumeroExemplaresDisponiveis();
    }

    public void registraObservador(ObservadorReserva observador){
        observadores.add(observador);
    }

    public boolean removeObservador(ObservadorReserva observador){
        for (int obj = 0; obj < observadores.size(); obj++) { 
            if(observador.getID() == observadores.get(obj).getID()){
                observadores.remove(obj);
                return true;
            }
        } 
        return false;
    }

    public void notificaObservadores(){
        for (ObservadorReserva obs : observadores) {
            obs.atualiza();
        }
    }

    public int getId(){
        return coDlivro;
    }

    public String getTitulo(){
        return titulo;
    }

    public LivroExemplar emprestarExemplarDisponivel(){
        for (LivroExemplar exp : exemplares) {
            if(exp.getStatus() == StatusExemplar.Disponivel){
                return exp;
            }
        }
        return null;
    }

    public void devolverExemplar(int codExp){
        for (LivroExemplar exp : exemplares) {
            if(exp.getCodExemplar() == codExp){
                exp.devolver();
                setEstadoExemplar(new ExemplarDisponivel());
                return;
            }
        }
    }

    public int getNumeroExemplaresDisponiveis(){
        int numero = 0;
        for (LivroExemplar exp : exemplares) {
            if(exp.getStatus() == StatusExemplar.Disponivel) numero++;
        }
        if(numero == 0) setEstadoExemplar(new ExemplarIndisponivel());
        return numero;
    }

    public void setEstadoExemplar(EstadoLivro novoEstado){
        this.estado = novoEstado;
    }
}

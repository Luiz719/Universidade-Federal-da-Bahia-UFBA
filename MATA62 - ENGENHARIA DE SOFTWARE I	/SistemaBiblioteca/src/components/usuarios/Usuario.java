package SistemaBiblioteca.src.components.usuarios;

import java.util.ArrayList;
import java.util.List;

import SistemaBiblioteca.src.components.Emprestimo;
import SistemaBiblioteca.src.components.Mensagem;
import SistemaBiblioteca.src.components.Reserva;
import SistemaBiblioteca.src.components.VerificadorEmprestimo;
import SistemaBiblioteca.src.components.livros.Livro;
import SistemaBiblioteca.src.components.livros.LivroExemplar;

public abstract class Usuario {
    private int codId;
    private String nome;
    private int tempoEmprestimo;
    private List<Emprestimo> emprestimos = new ArrayList<Emprestimo>();
    private List<Emprestimo> emprestimosFinalizados = new ArrayList<Emprestimo>();
    private int limiteEmprestimo;
    private List<Reserva> reservas = new ArrayList<Reserva>();
    private int limiteReserva = 3;
    private VerificadorEmprestimo verificador;
    private EstadoUsuarioEmprestimo estadoDevedor;
    private EstadoUsuarioEmprestimo estadoEmprestimo;
    private EstadoUsuarioReserva estadoReserva;

    public abstract boolean podeEmprestar();

    public boolean podeReservar(){
        return estadoReserva.podeReservar(this);
    }

    public boolean realizarReserva(Livro livro){

        if(estadoReserva.podeReservar(this)){
            Reserva novaReserva = new Reserva(livro, this);
            this.adicionarReserva(novaReserva);
            livro.adicionarReserva(novaReserva);
            return true;
        }
        return false;
    }

    public boolean realizarEmprestimo(Livro livro){

        if(this.getVerificador().autorizaEmprestimo(this, livro)){
            if(this.livroEstaReservado(livro.getId())){
                this.concluirReserva(livro.getId());
                livro.removeReserva(this.codId);
            }

            LivroExemplar exemplar = livro.emprestarExemplarDisponivel();

            Emprestimo novoEmprestimo = new Emprestimo(this, exemplar);
            this.adicionarEmprestimo(novoEmprestimo);

            exemplar.emprestar(novoEmprestimo);
            return true;
        }
        return false;
    }

    private void adicionarReserva(Reserva novaReserva){
        reservas.add(novaReserva);
        if(this.reservasDisponiveis() == 0){
            this.setEstadoReserva(new NoLimiteReserva());
        }
    }

    private void adicionarEmprestimo(Emprestimo novoEmprestimo){
        emprestimos.add(novoEmprestimo);
        if(this.emprestimosDisponiveis() == 0){
            this.setEstadoEmprestimo(new NoLimiteEmprestimo());
        }
    }

    public boolean concluirEmprestimo(Livro livro){
        for (int obj = 0; obj < emprestimos.size(); obj++) { 
            if(livro.getId() == emprestimos.get(obj).getCodLivro()){
                this.temEmprestimoAtrasado();

                Emprestimo emprestimo = emprestimos.get(obj);
                emprestimo.finalizar();

                livro.devolverExemplar(emprestimo.getCodExemplar());

                emprestimosFinalizados.add(emprestimo);
                emprestimos.remove(obj);
                setEstadoEmprestimo(new EmprestimoPossivel());
                return true;
            }
        } 
        
        Mensagem.emprestimoNaoEncontrado();
        return false;
    }

    public boolean concluirReserva(int codLivro){
        for (int obj = 0; obj < reservas.size(); obj++) { 
            if(codLivro == reservas.get(obj).getCodLivro()){
                reservas.remove(obj);
                this.setEstadoReserva(new ReservaPossivel());
                return true;
            }
        } 
        return false;
    }

    public String getNome(){
        return nome;
    }

    public void setNome(String novoNome){
        this.nome = novoNome;
    }

    public int getTempoEmprestimo() {
        return tempoEmprestimo;
    }

    public void setTempoEmprestimo(int tempo) {
        this.tempoEmprestimo = tempo;
    }

     public int getLimiteEmprestimo() {
        return limiteEmprestimo;
    }

    public void setLimiteEmprestimo(int limite) {
        this.limiteEmprestimo = limite;
    }

    public int getLimiteReserva(){
        return limiteReserva;
    }
    
    public int getID() {
        return codId;
    }

    public void setId(int id){
        this.codId = id;
    }

    public int reservasDisponiveis(){
        return limiteReserva - reservas.size();
    } 

    public int emprestimosDisponiveis(){
        return limiteEmprestimo - emprestimos.size();
    } 

    public VerificadorEmprestimo getVerificador(){
        return verificador;
    }

    public void setVerificador(VerificadorEmprestimo novoVerificador){
        this.verificador = novoVerificador;
    }

    public boolean livroEstaReservado(int codLivro){
        for (int obj = 0; obj < reservas.size(); obj++) { 
            if(codLivro == reservas.get(obj).getCodLivro()){
                return true;
            }
        } 
        return false;
    }

    public boolean exemplarEstaEmprestado(int codLivro){
        for (int obj = 0; obj < emprestimos.size(); obj++) { 
            if(codLivro == emprestimos.get(obj).getCodLivro()){
                return true;
            }
        } 
        return false;
    }

    public boolean temEmprestimoAtrasado(){
        for (Emprestimo emp : emprestimos) {
            if(emp.estarAtrasado()){
                this.setEstadoDevedor(new Devedor());
                return true;
            }
        }
        this.setEstadoDevedor(new NaoDevedor());
        return false;
    }

    public EstadoUsuarioEmprestimo getEstadoDevedor(){
        return this.estadoDevedor;
    }

    public void setEstadoDevedor(EstadoUsuarioEmprestimo estado){
        this.estadoDevedor = estado;
    }

    public EstadoUsuarioEmprestimo getEstadoEmprestimo(){
        return this.estadoEmprestimo;
    }

    public void setEstadoEmprestimo(EstadoUsuarioEmprestimo estado){
        this.estadoEmprestimo = estado;
    }

    public void setEstadoReserva(EstadoUsuarioReserva novoEstado){
        estadoReserva = novoEstado;
    }

    public int getNumeroEmprestimos() {
        return this.emprestimos.size();
    }

    public int getNumeroEmprestimosFinalizados() {
        return this.emprestimosFinalizados.size();
    }

    public int getNumeroReservas() {
        return this.reservas.size();
    }

    public Emprestimo getEmprestimo(int id) {
        return this.emprestimos.get(id);
    }

    public Emprestimo getEmprestimoFinalizado(int id) {
        return this.emprestimosFinalizados.get(id);
    }

    public Reserva getReserva(int id) {
        return this.reservas.get(id);
    }
}


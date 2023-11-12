package com.github.kallazz.invoicegenerator;

// GRASP: High Cohesion
public class Party {
    private String name;
    private String email;

    public Party(final String name, final String email) {
        this.name = name;
        this.email = email;
    }

    public String getName() {
        return this.name;
    }

    public String getEmail() {
        return this.email;
    }
}

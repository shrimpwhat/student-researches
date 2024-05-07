create table departments
(
    id             serial primary key,
    code           varchar(10)  not null,
    name           varchar(255) not null,
    research_count integer default 0
);

create table supervisors
(
    id             serial primary key,
    full_name      varchar(255) not null,
    email          varchar(255) unique,
    phone          varchar(30) unique,
    department     integer references departments (id),
    research_count integer default 0
);

create table students
(
    id         serial primary key,
    full_name  varchar(255) not null,
    email      varchar(255) unique,
    phone      varchar(30) unique,
    department integer references departments (id)
);

create table researches
(
    id          serial primary key,
    title       varchar(255) not null,
    department  integer references departments (id),
    field       varchar(255) not null,
    supervisor  integer references supervisors (id),
    url         varchar(500) not null,
    funding_sum integer default 0
);

create table students_researches
(
    student_id  integer references students (id),
    research_id integer references researches (id),
    primary key (student_id, research_id)
);

create table funding
(
    id       serial primary key,
    source   varchar(255),
    research integer references researches (id),
    amount   integer,
    date     date
);

create table reports
(
    id          serial primary key,
    name        varchar(255) not null,
    description varchar(500),
    date        date
);

create table research_reports
(
    research_id integer references researches (id),
    report_id   integer references reports (id),
    primary key (research_id, report_id)
);

--INDEXES
create index idx_students_name on students (full_name);
create index idx_supervisors_name on supervisors (full_name);
create index idx_researches_field on researches (field);

--FUNCTIONS
create or replace function add_department(_code varchar(10), _name varchar(255))
    returns void as
$$
begin
    insert into departments (code, name) values (_code, _name);
end;
$$ language plpgsql;

create or replace function edit_department(_id integer, _code varchar(10), _name varchar(255))
    returns void as
$$
begin
    update departments set code = _code, name = _name where id = _id;
end;
$$ language plpgsql;

create or replace function delete_department(_id integer)
    returns void as
$$
begin
    delete from departments where id = _id;
end;
$$ language plpgsql;


create or replace function add_supervisor(_full_name varchar(255), _email varchar(255), _phone_number varchar(30),
                                          _department integer)
    returns void as
$$
begin
    insert into supervisors (full_name, email, phone, department)
    values (_full_name, _email, _phone_number, _department);
end;
$$ language plpgsql;

create or replace function edit_supervisor(_id integer, _full_name varchar(255), _email varchar(255),
                                           _phone_number varchar(30), _department integer)
    returns void as
$$
begin
    update supervisors
    set full_name  = _full_name,
        email      = _email,
        phone      = _phone_number,
        department = _department
    where id = _id;
end;
$$ language plpgsql;

create or replace function delete_supervisor(_id integer)
    returns void as
$$
begin
    delete from supervisors where id = _id;
end;
$$ language plpgsql;

create or replace function add_student(_full_name varchar(255), _email varchar(255), _phone_number varchar(30),
                                       _department integer)
    returns void as
$$
begin
    insert into students (full_name, email, phone, department)
    values (_full_name, _email, _phone_number, _department);
end;
$$ language plpgsql;

create or replace function edit_student(_id integer, _full_name varchar(255), _email varchar(255),
                                        _phone_number varchar(30), _department integer)
    returns void as
$$
begin
    update students
    set full_name  = _full_name,
        email      = _email,
        phone      = _phone_number,
        department = _department
    where id = _id;
end;
$$ language plpgsql;

create or replace function delete_student(_id integer)
    returns void as
$$
begin
    delete from students where id = _id;
end;
$$ language plpgsql;


create or replace function add_research(_title varchar(255), _department integer, _field varchar(255),
                                        _supervisor integer, _url varchar(500))
    returns void
    language plpgsql as
$$
begin
    insert into researches (title, department, field, supervisor, url)
    values (_title, _department, _field, _supervisor, _url);
end;
$$;


create or replace function edit_research(_id integer, _title varchar(255), _department integer, _field varchar(255),
                                         _supervisor integer, _url varchar(500))
    returns void as
$$
begin
    update researches
    set title      = _title,
        department = _department,
        field      = _field,
        supervisor = _supervisor,
        url        = _url
    where id = _id;
end;
$$ language plpgsql;


create or replace function delete_research(_id integer)
    returns void as
$$
begin
    delete from researches where id = _id;
end;
$$ language plpgsql;


create or replace function assign_research(_student integer, _research integer)
    returns void as
$$
begin
    insert into students_researches values (_student, _research);
end;
$$ language plpgsql;


create or replace function unassign_research(_student integer, _research integer)
    returns void as
$$
begin
    delete from students_researches where student_id = _student and research_id = _research;
end;
$$ language plpgsql;


create or replace function add_funding(_source varchar(255), _research integer, _amount integer, _date date)
    returns void as
$$
begin
    insert into funding (source, research, amount, date) values (_source, _research, _amount, _date);
end;
$$ language plpgsql;


create or replace function edit_funding(_id integer, _source varchar(255), _research integer, _amount integer,
                                        _date date)
    returns void as
$$
begin
    update funding
    set source   = _source,
        research = _research,
        amount   = _amount,
        date     = _date
    where id = _id;
end;
$$ language plpgsql;

create or replace function delete_funding(_id integer)
    returns void as
$$
begin
    delete from funding where id = _id;
end;
$$ language plpgsql;


create or replace function add_report(_name varchar(255), _description varchar(500), _date date)
    returns void as
$$
begin
    insert into reports (name, description, date) values (_name, _description, _date);
end;
$$ language plpgsql;


create or replace function edit_report(_id integer, _name varchar(255), _description varchar(500), _date date)
    returns void as
$$
begin
    update reports
    set name        = _name,
        description = _description,
        date        = _date
    where id = _id;
end;
$$ language plpgsql;


create or replace function delete_report(_id integer)
    returns void as
$$
begin
    delete from reports where id = _id;
end;
$$ language plpgsql;


create or replace function modify_department_research_count(_id integer, _dif integer)
    returns void as
$$
begin
    if _id is null then
        return;
    end if;

    update departments
    set research_count = research_count + _dif
    where id = _id;
end;
$$ language plpgsql;

create or replace function modify_supervisor_research_count(_id integer, _dif integer)
    returns void as
$$
begin
    if _id is null then
        return;
    end if;

    update supervisors
    set research_count = research_count + _dif
    where id = _id;
end;
$$ language plpgsql;

create or replace function modify_departments_supervisors_research_count()
    returns trigger as
$$
begin
    case tg_op
        when 'INSERT' then begin
            perform modify_department_research_count(new.department, 1);
            perform modify_supervisor_research_count(new.supervisor, 1);
        end;
        when 'DELETE' then begin
            perform modify_department_research_count(old.department, -1);
            perform modify_supervisor_research_count(old.supervisor, -1);
        end;
        end case;
    return new;
end;
$$ language plpgsql;


create or replace function modify_research_count(_table varchar, _id integer, _dif integer)
    returns void as
$$
begin
    case _table
        when 'departments' then perform modify_department_research_count(_id, _dif);
        when 'supervisors' then perform modify_supervisor_research_count(_id, _dif);
        end case;
end;
$$ language plpgsql;

create or replace function on_update_research()
    returns trigger as
$$
begin
    if old = new then
        return new;
    end if;

    if old.department <> new.department then
        perform modify_research_count('departments', old.department, -1);
        perform modify_research_count('departments', new.department, 1);
    end if;

    if old.supervisor <> new.supervisor then
        perform modify_research_count('supervisors', old.supervisor, -1);
        perform modify_research_count('supervisors', new.supervisor, 1);
    end if;

    return new;
end;
$$ language plpgsql;

create or replace function on_delete_department()
    returns trigger as
$$
begin
    update researches set department = null where department = old.id;
    update supervisors set department = null where department = old.id;
    update students set department = null where department = old.id;
    return new;
end;
$$ language plpgsql;

create or replace function on_delete_supervisor()
    returns trigger as
$$
begin
    update researches set supervisor = null where supervisor = old.id;
    return new;
end;
$$ language plpgsql;


create or replace function on_delete_student()
    returns trigger as
$$
begin
    delete from students_researches where student_id = old.id;
    return new;
end
$$ language plpgsql;


create or replace function on_delete_report()
    returns trigger as
$$
begin
    delete from research_reports where report_id = old.id;
    return new;
end
$$ language plpgsql;


create or replace function on_insert_funding()
    returns trigger as
$$
begin
    update researches set funding_sum = funding_sum + new.amount where id = new.research;
    return new;
end
$$ language plpgsql;


create or replace function on_delete_funding()
    returns trigger as
$$
begin
    update researches set funding_sum = funding_sum - old.amount where id = old.research;
    return new;
end
$$ language plpgsql;


create or replace function on_update_funding()
    returns trigger as
$$
begin
    update researches set funding_sum = funding_sum - old.amount where id = old.research;
    update researches set funding_sum = funding_sum + new.amount where id = new.research;
    return new;
end
$$ language plpgsql;


create or replace function assign_report(_research integer, _report integer)
    returns void as
$$
begin
    insert into research_reports values (_research, _report);
end;
$$ language plpgsql;


create or replace function unassign_report(_research integer, _report integer)
    returns void as
$$
begin
    delete from research_reports where research_id = _research and report_id = _report;
end;
$$ language plpgsql;


--TRIGGERS
create trigger researches_insert_or_delete
    after insert or delete
    on researches
    for each row
execute function modify_departments_supervisors_research_count();


create trigger researches_update
    after update of department, supervisor
    on researches
    for each row
execute function on_update_research();


create trigger departments_delete
    after delete
    on departments
    for each row
execute function on_delete_department();


create trigger supervisors_delete
    after delete
    on supervisors
    for each row
execute function on_delete_supervisor();


create trigger students_delete
    after delete
    on students
    for each row
execute function on_delete_student();


create trigger reports_delete
    after delete
    on reports
    for each row
execute function on_delete_report();


create trigger funding_insert
    after insert
    on funding
    for each row
execute function on_insert_funding();


create trigger funding_delete
    after delete
    on funding
    for each row
execute function on_delete_funding();


create trigger funding_update
    after update
    on funding
    for each row
execute function on_update_funding();
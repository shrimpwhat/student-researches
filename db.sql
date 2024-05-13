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
    id       serial primary key,
    name     varchar(255) not null,
    date     date,
    research integer references researches (id)
);


--INDEXES
create index idx_researches_title on researches (title);
create index idx_students_name on students (lower(full_name));
create index idx_supervisors_name on supervisors using brin (full_name);


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


create or replace function add_report(_name varchar(255), _date date, _research integer)
    returns void as
$$
begin
    insert into reports (name, date, research) values (_name, _date, _research);
end;
$$ language plpgsql;


create or replace function edit_report(_id integer, _name varchar(255), _date date,
                                       _research integer)
    returns void as
$$
begin
    update reports
    set name     = _name,
        date     = _date,
        research = _research
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


create or replace procedure assign_research_to_students(_research integer, _students integer[])
    language plpgsql
as
$$
begin
    for student in _students
        loop
            insert into students_researches values (student, _research);
        end loop;
end
$$;


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


-- TASKS
-- 3.a
create type statuses as
(
    Название               varchar(255),
    "Сумма финансирования" bigint,
    "Статус"               text
);
create or replace function get_research_statuses()
    returns setof statuses
as
$$
select r.title,
       sum(f.amount),
       case
           when sum(f.amount) = 0 then 'Без финансирования'
           when sum(f.amount) < 10000 then 'Небольшое финансирование'
           when sum(f.amount) < 50000 then 'Среднее финансирование'
           else 'Большое финансирование'
           end
from researches as r
         join funding as f on r.id = f.research
group by r.title;
$$ language sql;

-- 3.b
create view supervisors_view as
select s.*, d.name, d.code
from supervisors as s
         join departments as d on s.department = d.id;

create or replace function supervisors_view_insert()
    returns trigger
as
$$
declare
    dep_id integer;
begin
    if new.department is null then
        insert into departments (code, name) values (new.code, new.name) returning id into dep_id;
    else
        dep_id = new.department;
    end if;
    insert into supervisors (full_name, department) values (new.full_name, dep_id);
    return null;
end
$$ language plpgsql;


create trigger on_supervisors_view_insert
    instead of insert
    on supervisors_view
    for each row
execute function supervisors_view_insert();


create or replace function supervisors_view_update()
    returns trigger
as
$$
begin
    update supervisors
    set full_name  = new.full_name,
        department = new.department
    where id = old.id;

    if old.department = new.department then
        update departments
        set code = new.code,
            name = new.name
        where id = old.department;
    end if;
    return null;
end
$$ language plpgsql;


create trigger on_supervisors_view_update
    instead of update
    on supervisors_view
    for each row
execute function supervisors_view_update();


create or replace function supervisors_view_delete()
    returns trigger
as
$$
begin
    delete from supervisors where id = old.id;
    return null;
end
$$ language plpgsql;


create trigger on_supervisors_view_delete
    instead of delete
    on supervisors_view
    for each row
execute function supervisors_view_delete();


--3.c
create materialized view students_view as
select *
from students;


--3.d подзапрос в from
create or replace function get_students_researches(_student integer)
    returns character varying
as
$$
select title
from (select *
      from researches
      where id in (select research_id from students_researches where student_id = _student)) as r
$$ language sql;


--3.e
create or replace function get_students()
    returns setof students
as
$$
select s.*
from students as s
where exists(select * from departments as d where d.id = s.department);
$$ language sql;


create or replace function get_researches()
    returns setof researches
as
$$
select r.*
from researches as r
where exists(select * from supervisors as s where s.id = r.supervisor);
$$ language sql;


create or replace function get_funding()
    returns setof funding
as
$$
select f.*
from funding as f
where exists(select * from researches as r where r.id = f.research);
$$ language sql;